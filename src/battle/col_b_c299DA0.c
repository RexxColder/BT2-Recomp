#define ColLine_DistSqPoint Quat_LengthSq  /* fix_targets */ /* the original uses 0x299d70 here */
/*
 * Collision primitive library, second part: 0x236190..0x239BB0 (include/battle/col_b.h has the shapes).
 *
 * Tests between spheres, segments, capsules, triangles and oriented boxes, the bounds builders the mesh walks are
 * fed with, and the shape builders every projectile's AddHit function calls. The first part (boxes, the mesh
 * walk, box against box) is src/battle/col_a.c.
 *
 * SIMULATION. Called by the stage collision (StgCol_*), the projectile hit detection (EftDet_*), the fighter body
 * test (BtlBodyHit_TestVolumes), the sight / approach / sweeping-beam segment traces and the debris bodies.
 *   - No function here contains VU0 code of its own, draws a random number or keeps state: there is no static
 *     buffer. Every result goes to the caller's pointers.
 *   - The arithmetic is of two kinds, and a port must keep both exactly:
 *       * sums of products written out in C (single-precision FPU, evaluated in the order of the source);
 *       * calls of the VU0 vector routines at 0x121E28.. (Vec4_Sub, Vec3_Dot, Vec3_Cross, Vec3_Normalize, ...),
 *         see the list below. Which of the two a given dot product uses is part of the behaviour.
 *   - sqrtf is the FPU instruction (the libm call only when the result is NaN, which a negative input gives).
 *
 * Sources recognised (the C below matches the original instructions, so the formulas are theirs):
 *   - ColTri_DistSqPoint: the point / triangle squared distance of the Magic Software library (MgcDist3DVecTri),
 *     with one check added in front.
 *   - ColSeg_NearestOnLine / NearestParallel / AdjustNearest / Nearest: "Fast, robust intersection of 3D line
 *     segments" (Game Programming Gems 2): FindNearestPointOnLineSegment, FindNearestPointOfParallelLineSegments,
 *     AdjustNearestPoints, IntersectLineSegments, with epsilon = 1e-6 and infinite_lines = false.
 *   - ColSphere_TestLine: the classic line / sphere quadratic (a, b, c, b*b - 4ac).
 *
 * Original bugs kept (all verified by the matching C):
 *   - ColSphere_ContactObb: when the centre is in front of a z face the normal is (axis[2].x, axis[2].x,
 *     axis[2].x) * sign(z), and in front of a y face (axis[1].x, axis[1].x, axis[1].x) * sign(z): the wrong
 *     components, and for the y face the wrong sign. Only the x face is right.
 *   - ColSphere_ContactSphere (no caller): the contact point is measured from a's centre with b's radius.
 *   - ColSweep_TestTri computes the vector from the contact to the centre (`off`) in all three cases and never
 *     returns it.
 */
#include "common.h"
#include "battle/col_b.h"

extern f32 sqrtf(f32 x);

/* VU0 vector routines (0x121E28..0x122230), hand-written macro-mode code outside this file:
     Vec4_Copy   128-bit move.
     Vec4_Add / Vec4_Sub   all four components (so the difference of two positions has w = 0).
     Vec4_Scale  all four components times s; Vec3_Scale  x, y, z times s, w copied from the input.
     Vec3_Dot    (x*x' + y*y') + VF3.x * (z*z'): three VU0 products, then two VU0 additions in that order. VF3 is
                 (1, 0, 0, 0), loaded once at boot (0x120088) and expected to stay.
     Vec3_Cross  out = a x b, w = 0.
     Vec3_Normalize   len = VU0 sqrt of the dot above, then q = 1 / len (VU0 divide), out.xyz = v.xyz * q, w = 0:
                 a multiplication by the reciprocal, not a division. A zero vector gives (0, 0, 0, 0).
     Vec3_LengthSq    squared length (the same sum as Vec3_Dot); Vec3_Dist  distance of two points (VU0 sqrt). */
extern void Vec4_Copy(CpVec *dst, CpVec *src);
extern void Vec4_Add(CpVec *out, CpVec *a, CpVec *b);
extern void Vec4_Sub(CpVec *out, CpVec *a, CpVec *b);
extern void Vec4_Scale(CpVec *out, CpVec *v, f32 s);
extern void Vec3_Scale(CpVec *out, CpVec *v, f32 s);
extern f32 Vec3_Dot(CpVec *a, CpVec *b);
extern void Vec3_Cross(CpVec *out, CpVec *a, CpVec *b);
extern void Vec3_Normalize(CpVec *out, CpVec *v);
extern f32 Vec3_LengthSq(CpVec *v);            /* squared length */
extern f32 Vec3_Dist(CpVec *a, CpVec *b);  /* distance between two points */

/* Box helpers (col_a.c). */
extern void StgAabb_SetEmpty(CpBox *box);
extern void ColBox_AddPoint(CpBox *box, CpVec *pt);


/* "No hit yet": 0x7F7FFFFE, one bit below FLT_MAX (this compiler's reading of the literal). It is too large for
   the assembler's li.s, so the compiler keeps it as a 4-byte constant in .sdata, one per function that uses it,
   read with lui / lwc1: 0x2FEBAC is ColSweep_TestTri's (this object's whole .sdata). */
#define CP_FLT_MAX 3.402823466e+38F
#define CP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CP_MIN(a, b) ((a) > (b) ? (b) : (a))
#define CP_OUT_OF_RANGE(a) ((a) < 0.0f || (a) > 1.0f)

/* Two 2D lines p + t (q - p) and r + u (s - r): writes t of their crossing; 0 when they are parallel. */
s32 ColLine2_Intersect(f32 *p, f32 *q, f32 *r, f32 *s, f32 *t);

/* A sphere moved along sw->dir against a triangle: the distance travelled until the first touch and the centre's
   position there (x, y, z only). The distance is NOT limited to sw->length: the caller compares it.
     - Rejected at once when dir . normal > -0.001 (moving away or along the face) or when the start centre is
       more than a radius behind the plane.
     - Face: only when the start centre is more than a radius in front of the plane; the centre's position at the
       moment of touching must project inside the triangle (ColTri_ContainsPoint).
     - Corners: the line from each corner against the direction, cut with the start sphere; the smaller root, not
       negative. Replaces the best so far only when strictly smaller (face and earlier corners win ties).
     - Edges: in the plane holding the edge and the direction, the circle the sphere cuts out of that plane is
       moved along dir until it touches the line a..b (solved in 2D after dropping the plane normal's largest
       component: x only when |x| is strictly the largest, else y when |y| > |z|, else z); the touching point must
       lie between a and b (ends included). Replaces the best so far when smaller OR EQUAL (an edge wins ties
       against the face, a corner or an earlier edge).
   Edges are a (v[i]) .. b (v[i + 1], v[0] after v[2]). */
s32 ColSweep_TestTri(CpSweep *sw, CpTri *tri, CpVec *pos, f32 *dist);

/* Segment a..b against the front side of a triangle (the side (v1 - v0) x (v2 - v0) points to; the stored plane
   is not used): the crossing point (w = 1) and its fraction along the segment, both ends and the triangle's edges
   included. A segment parallel to the plane or coming from behind misses. *dist is also written (with an
   unscaled value) when the test fails after the plane check. */
s32 ColSeg_TestTri(CpSeg *seg, CpTri *tri, CpVec *pos, f32 *dist);

/* Sphere against an oriented box: contact normal, the point of the sphere's surface facing the box and the
   depth. Two of the three face cases use the wrong axis components (see the header notes). */
s32 ColSphere_ContactObb(CpSphere *sph, CpObb *obb, CpVec *nrm, CpVec *pos, f32 *depth);

/* Sphere against an oriented box, yes or no. */
s32 ColSphere_TestObb(CpSphere *sph, CpObb *obb);

/* Ray (origin, unit direction) against a sphere: distance to the entry point, 0 when the origin is inside. */
s32 ColSphere_TestRay(CpSphere *sph, CpRay *ray, f32 *t, CpVec *pos);

/* The line a + t (b - a) against a sphere: number of roots (1 or 2) and both parameters, larger root first. */
s32 ColSphere_TestLine(CpSphere *sph, CpVec *a, CpVec *b, s32 *count, f32 *t0, f32 *t1);

/* Two spheres overlap or touch. */
s32 ColSphere_TestSphere(CpSphere *a, CpSphere *b);

/* Two spheres overlap: unit normal from b to a, a contact point and the depth. */
s32 ColSphere_ContactSphere(CpSphere *a, CpSphere *b, CpVec *nrm, CpVec *pos, f32 *depth);

/* Two spheres moving by moveA / moveB during the frame: the fraction of the frame at which they first touch.
   Returns 1 with *t = 0 when they overlap at the start (strictly: centres closer than the radii). Returns 0 when
   the squared relative movement is below 1.1754944e-36, when they are not approaching (relative movement .
   offset >= 0) or when the paths never touch. *t is not limited to 0..1: the caller tests it. */
s32 ColSphere_SweepSphere(CpSphere *a, CpSphere *b, CpVec *moveA, CpVec *moveB, f32 *t);

/* Two spheres that touch (or are no more than 0.001 apart): the unit direction a -> b ((1, 0, 0) when the centres
   coincide) and each centre moved half the overlap plus 0.001 away from the other (x, y, z only). */
s32 ColSphere_SeparateSphere(CpSphere *a, CpSphere *b, CpVec *posA, CpVec *posB, CpVec *nrm);

/* Squared distance from a point to a triangle, with the parameters (s along v0->v1, t along v0->v2) of the
   nearest point. A degenerate triangle gives 1e8 and leaves s and t unwritten. */
f32 ColTri_DistSqPoint(CpVec *pt, CpTri *tri, f32 *s, f32 *t);

/* The point v0 + s (v1 - v0) + t (v2 - v0) of a triangle. */
void ColTri_GetPoint(CpVec *out, CpTri *tri, f32 s, f32 t);

/* Sphere touches a triangle (squared distance <= sph->radiusSq, the stored field): writes the triangle's point
   nearest to the centre (w = 1). */
s32 ColSphere_TestTri(CpVec *pos, CpSphere *sph, CpTri *tri);

/* Axis-aligned bounds of a capsule. */
void ColBounds_OfCapsule(CpBox *box, CpCapsule *cap);

/* Axis-aligned bounds of a sphere. */
void ColBounds_OfSphere(CpBox *box, CpSphere *sph);

/* Ray of a segment: origin a, unit direction towards b. */
void ColRay_FromSeg(CpRay *ray, CpSeg *seg);

/* Grows a box to contain a sphere. */
void ColBounds_AddSphere(CpBox *box, CpSphere *sph);

/* Axis-aligned bounds of an oriented box (its eight world corners). */
void ColBounds_OfObb(CpBox *box, CpObb *obb);

/* Axis-aligned bounds of a segment. */
void ColBounds_OfSeg(CpBox *box, CpSeg *seg);

/* The segment of a capsule lengthened by the radius at both ends. */
void ColCapsule_GetLongSeg(CpSeg *out, CpCapsule *cap);

/* The same, also returning the unit direction (w = 1). */
void ColCapsule_GetLongSegDir(CpSeg *out, CpVec *dir, CpCapsule *cap);

/* Sphere around a capsule: centre at the middle, radius = half the length + the capsule's radius. */
void ColCapsule_GetBoundSphere(CpSphere *out, CpCapsule *cap);

/* Nearest points of two segments (copies of both are handed to ColSeg_Nearest); 1 when the segments cross, and
   only then is w of the two points set to 1. No caller. */
s32 ColSeg_ClosestToSeg(CpSeg *a, CpSeg *b, CpVec *onA, CpVec *onB);

/* Squared distance from a point to the infinite line a..b; `out` gets the foot of the perpendicular. */
f32 ColLine_DistSqPoint(CpVec *pt, CpVec *a, CpVec *b, CpVec *out);

/* Distance from a point to the infinite line a..b. */
f32 func_00299DA0(CpVec *pt, CpVec *a, CpVec *b, CpVec *out) {
    return sqrtf(ColLine_DistSqPoint(pt, a, b, out));
}

/* Nearest point to b on the line (or segment) a + param * l. A line shorter than sqrt(epsSq) gives a and leaves
   param unwritten. */
void ColSeg_NearestOnLine(CpVec *a, CpVec *l, CpVec *b, s32 infinite, f32 epsSq, CpVec *out, f32 *param);

/* Nearest points of two parallel segments. */
void ColSeg_NearestParallel(CpSeg *a, CpVec *la, CpSeg *b, CpVec *lb, s32 infinite, f32 epsSq, CpVec *onA,
                            CpVec *onB);

/* Nearest points of two segments when a parameter of the infinite-line solution fell outside [0, 1]. */
void ColSeg_AdjustNearest(CpVec *a, CpVec *la, CpVec *b, CpVec *lb, f32 epsSq, f32 s, f32 t, CpVec *onA,
                          CpVec *onB);

/* Nearest points of two segments (x, y, z); returns 1 when they are closer than 1e-6 (sum of the component
   distances). Tolerances: a segment whose squared length is below 1e-6 * 1e-6 is a point; the segments are
   parallel when |L11 L22 - L12^2| < 1e-6; the helpers get 1e-6 (not its square) as their squared tolerance, as in
   the published routine. The midpoint and the difference of the two points are computed and dropped. */
s32 ColSeg_Nearest(CpSeg *a, CpSeg *b, CpVec *onA, CpVec *onB);

/* Builds a capsule: the "box" shape of a hit record (a segment from `a` to `b` with a radius). */
void ColCapsule_Set(CpCapsule *cap, CpVec *a, CpVec *b, f32 radius);

/* Midpoint of a segment (w = 1). */
void ColSeg_GetMidpoint3(CpVec *out, CpSeg *seg);

/* Builds the swept sphere of a capsule: start sphere, movement, unit direction and length. */
void ColSweep_FromCapsule(CpSweep *sw, CpCapsule *cap);

/* Plane through three points: unit normal (c - b) x (a - b), w = -(normal . a). */
void ColPlane_FromPoints(CpVec *plane, CpVec *a, CpVec *b, CpVec *c);

/* Projects a point onto a plane (normal . p + w = 0). */
void ColPlane_ProjectPoint(CpVec *out, CpVec *plane, CpVec *pt);

/* Signed distance of a point from a plane stored as normal . p = w. */
f32 ColPlane_DistPoint(CpVec *plane, CpVec *pt);

/* Builds a segment from two points (w = 1). Same code as ColSeg_Set; no caller. */
void ColSeg_Set2(CpSeg *seg, CpVec *a, CpVec *b);

/* Builds a segment from two points (w = 1): what StgCol_TraceSegment takes. */
void ColSeg_Set(CpSeg *seg, CpVec *a, CpVec *b);

/* Midpoint of a segment (w = 1). */
void ColSeg_GetMidpoint(CpSeg *seg, CpVec *out);

/* Builds a sphere: the "sphere" shape of a hit record. */
void ColSphere_Set(CpSphere *sph, CpVec *pos, f32 radius);

/* Builds a triangle from three corners and a plane. */
void ColTri_Set(CpTri *tri, CpVec *a, CpVec *b, CpVec *c, CpVec *nrm);

/* A point of the triangle's plane lies inside the triangle (edges included). */
s32 ColTri_ContainsPoint(CpTri *tri, CpVec *pt);
