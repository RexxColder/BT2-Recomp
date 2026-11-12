/*
 * BT2 0x292750..0x295F80: collision primitive library, second part (BT3 src/battle/col_b.c, same code; read that
 * file's header for what the functions do and the original bugs they keep).
 *
 * Differences from BT3 (verified by the matching C):
 *   - no ColSphere_TestObb and no ColPlane_DistPoint;
 *   - the module keeps two hand-written VU0 routines of its own (squared length at 0x293BE0, distance of two points
 *     at 0x294750) where BT3 calls the shared vector library;
 *   - the vector routines it calls are the copies at 0x312490.. (sceVu0 library), not the ones at 0x129xxx;
 *   - ColTri_Set sits at the address the SDK signatures named sceVu0LightColorMatrix.
 */
#include "common.h"
#include "battle/col_b.h"

/* BT2 targets of the vector calls (the sceVu0 library copy, checked against the original relocations). */
#define Vec4_Copy func_003126C8
#define Vec4_Add func_00312638
#define Vec4_Sub func_00312650
#define Vec4_Scale func_00312680
#define Vec3_Scale func_00312FB0
#define Vec3_Cross func_00312490
#define Vec3_Dot sceVu0InnerProduct
#define Vec3_Normalize sceVu0Normalize
#define Vec3_LengthSq ColB_Vec3LengthSq
#define Vec3_Dist ColB_Vec3Dist

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
/* Float constants of the module: the original reads them from the data labels below (gp-relative for the small
   ones, lui/lwc1 for D_00387D8C, which is not in $gp reach). Values checked against the data: 0x387188 -1e-3,
   0x38718C 1e-4, 0x387190 and 0x387194 1e-3, 0x387198 1e-9, 0x38719C 1e8, 0x3871A0 1e-4, 0x3871A4 1e-12,
   0x3871A8 and 0x3871AC 1e-6, 0x3871B0 1e-3, 0x387D8C FLT_MAX (3.402823264e+38). */
extern f32 D_00387D8C[];
extern f32 D_00387188;
extern f32 D_0038718C;
extern f32 D_00387190;
extern f32 D_00387194;
extern f32 D_00387198;
extern f32 D_0038719C;
extern f32 D_003871A0;
extern f32 D_003871A4;
extern f32 D_003871A8;
extern f32 D_003871AC;
extern f32 D_003871B0;
#define CP_FLT_MAX (D_00387D8C[0])
#define CP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define CP_MIN(a, b) ((a) > (b) ? (b) : (a))
#define CP_OUT_OF_RANGE(a) ((a) < 0.0f || (a) > 1.0f)

/* Segment a..b against the front side of a triangle (the side (v1 - v0) x (v2 - v0) points to; the stored plane
   is not used): the crossing point (w = 1) and its fraction along the segment, both ends and the triangle's edges
   included. A segment parallel to the plane or coming from behind misses. *dist is also written (with an
   unscaled value) when the test fails after the plane check. */
s32 ColSeg_TestTri(CpSeg *seg, CpTri *tri, CpVec *pos, f32 *dist) {
    CpVec e1;
    CpVec e2;
    CpVec n;
    CpVec d;
    CpVec c;
    CpVec w;
    f32 det;
    f32 u;
    f32 v;
    f32 inv;
    f32 k;
    s32 ret;

    Vec4_Sub(&e1, &tri->v[1], &tri->v[0]);
    Vec4_Sub(&e2, &tri->v[2], &tri->v[0]);
    Vec4_Sub(&d, &seg->a, &seg->b);
    Vec3_Cross(&n, &e1, &e2);
    det = Vec3_Dot(&d, &n);
    if (det <= 0.0f) {
        return 0;
    }
    Vec4_Sub(&w, &seg->a, &tri->v[0]);
    *dist = Vec3_Dot(&w, &n);
    if (*dist < 0.0f) {
        return 0;
    }
    if (*dist > det) {
        return 0;
    }
    Vec3_Cross(&c, &d, &w);
    u = Vec3_Dot(&e2, &c);
    if (u < 0.0f || u > det) {
        return 0;
    }
    v = -Vec3_Dot(&e1, &c);
    if (v < 0.0f || u + v > det) {
        return 0;
    }
    ret = 1;
    inv = 1.0f / det;
    u *= inv;
    v *= inv;
    *dist *= inv;
    k = 1.0f - u - v;
    pos->x = tri->v[0].x * k + tri->v[1].x * u + tri->v[2].x * v;
    pos->y = tri->v[0].y * k + tri->v[1].y * u + tri->v[2].y * v;
    pos->z = tri->v[0].z * k + tri->v[1].z * u + tri->v[2].z * v;
    pos->w = 1.0f;
    return ret;
}

/* Sphere against an oriented box: contact normal, the point of the sphere's surface facing the box and the
   depth. Two of the three face cases use the wrong axis components (see the header notes). */
s32 ColSphere_ContactObb(CpSphere *sph, CpObb *obb, CpVec *nrm, CpVec *pos, f32 *depth) {
    CpVec d;
    CpVec p;
    CpVec loc;
    CpVec l;
    f32 sx;
    f32 sy;
    f32 sz;

    Vec4_Sub(&d, &sph->pos, &obb->center);
    loc.x = d.x * obb->axis[0].x + d.y * obb->axis[0].y + d.z * obb->axis[0].z;
    loc.y = d.x * obb->axis[1].x + d.y * obb->axis[1].y + d.z * obb->axis[1].z;
    loc.z = d.x * obb->axis[2].x + d.y * obb->axis[2].y + d.z * obb->axis[2].z;
    sz = 1.0f;
    sy = 1.0f;
    sx = 1.0f;
    Vec4_Copy(&p, &loc);
    if (p.x < 0.0f) {
        p.x = -p.x;
        sx = -1.0f;
    }
    if (p.y < 0.0f) {
        p.y = -p.y;
        sy = -1.0f;
    }
    if (p.z < 0.0f) {
        p.z = -p.z;
        sz = -1.0f;
    }
    p.x -= obb->half.x;
    p.y -= obb->half.y;
    p.z -= obb->half.z;
    if (p.x > sph->radius || p.y > sph->radius || p.z > sph->radius) {
        return 0;
    }
    if (p.x < 0.0f) {
        if (p.y < 0.0f) {
            nrm->x = obb->axis[2].x * sz;
            nrm->y = obb->axis[2].x * sz;
            nrm->z = obb->axis[2].x * sz;
            pos->x = sph->pos.x - nrm->x * sph->radius;
            pos->y = sph->pos.y - nrm->y * sph->radius;
            pos->z = sph->pos.z - nrm->z * sph->radius;
            *depth = sph->radius - p.z;
            return 1;
        } else if (p.z < 0.0f) {
            nrm->x = obb->axis[1].x * sz;
            nrm->y = obb->axis[1].x * sz;
            nrm->z = obb->axis[1].x * sz;
            pos->x = sph->pos.x - nrm->x * sph->radius;
            pos->y = sph->pos.y - nrm->y * sph->radius;
            pos->z = sph->pos.z - nrm->z * sph->radius;
            *depth = sph->radius - p.y;
            return 1;
        } else {
            f32 dd = p.y * p.y + p.z * p.z;
            f32 dist;

            if (dd <= sph->radius * sph->radius) {
                dist = sqrtf(dd);
                l.x = 0.0f;
                l.y = sy * p.y / dist;
                l.z = sz * p.z / dist;
                nrm->x = obb->axis[0].x * l.x + l.y * obb->axis[1].x + l.z * obb->axis[2].x;
                nrm->y = obb->axis[0].y * l.x + l.y * obb->axis[1].y + l.z * obb->axis[2].y;
                nrm->z = obb->axis[0].z * l.x + l.y * obb->axis[1].z + l.z * obb->axis[2].z;
                pos->x = sph->pos.x - nrm->x * sph->radius;
                pos->y = sph->pos.y - nrm->y * sph->radius;
                pos->z = sph->pos.z - nrm->z * sph->radius;
                *depth = sph->radius - dist;
                return 1;
            }
        }
    } else if (p.y < 0.0f) {
        if (p.z < 0.0f) {
            nrm->x = obb->axis[0].x * sx;
            nrm->y = obb->axis[0].y * sx;
            nrm->z = obb->axis[0].z * sx;
            pos->x = sph->pos.x - nrm->x * sph->radius;
            pos->y = sph->pos.y - nrm->y * sph->radius;
            pos->z = sph->pos.z - nrm->z * sph->radius;
            *depth = sph->radius - p.x;
            return 1;
        } else {
            f32 dd = p.x * p.x + p.z * p.z;
            f32 dist;

            if (dd <= sph->radius * sph->radius) {
                dist = sqrtf(dd);
                l.y = 0.0f;
                l.x = sx * p.x / dist;
                l.z = sz * p.z / dist;
                nrm->x = l.x * obb->axis[0].x + obb->axis[1].x * l.y + l.z * obb->axis[2].x;
                nrm->y = l.x * obb->axis[0].y + obb->axis[1].y * l.y + l.z * obb->axis[2].y;
                nrm->z = l.x * obb->axis[0].z + obb->axis[1].z * l.y + l.z * obb->axis[2].z;
                pos->x = sph->pos.x - nrm->x * sph->radius;
                pos->y = sph->pos.y - nrm->y * sph->radius;
                pos->z = sph->pos.z - nrm->z * sph->radius;
                *depth = sph->radius - dist;
                return 1;
            }
        }
    } else if (p.z < 0.0f) {
        f32 dd = p.x * p.x + p.y * p.y;
        f32 dist;

        if (dd <= sph->radius * sph->radius) {
            dist = sqrtf(dd);
            l.z = 0.0f;
            l.x = sx * p.x / dist;
            l.y = sy * p.y / dist;
            nrm->x = l.x * obb->axis[0].x + l.y * obb->axis[1].x + obb->axis[2].x * l.z;
            nrm->y = l.x * obb->axis[0].y + l.y * obb->axis[1].y + obb->axis[2].y * l.z;
            nrm->z = l.x * obb->axis[0].z + l.y * obb->axis[1].z + obb->axis[2].z * l.z;
            pos->x = sph->pos.x - nrm->x * sph->radius;
            pos->y = sph->pos.y - nrm->y * sph->radius;
            pos->z = sph->pos.z - nrm->z * sph->radius;
            *depth = sph->radius - dist;
            return 1;
        }
    } else {
        f32 dd = p.x * p.x + p.y * p.y + p.z * p.z;
        f32 dist;

        if (dd <= sph->radius * sph->radius) {
            dist = sqrtf(dd);
            l.x = sx * p.x / dist;
            l.y = sy * p.y / dist;
            l.z = sz * p.z / dist;
            nrm->x = l.x * obb->axis[0].x + l.y * obb->axis[1].x + l.z * obb->axis[2].x;
            nrm->y = l.x * obb->axis[0].y + l.y * obb->axis[1].y + l.z * obb->axis[2].y;
            nrm->z = l.x * obb->axis[0].z + l.y * obb->axis[1].z + l.z * obb->axis[2].z;
            pos->x = sph->pos.x - nrm->x * sph->radius;
            pos->y = sph->pos.y - nrm->y * sph->radius;
            pos->z = sph->pos.z - nrm->z * sph->radius;
            *depth = sph->radius - dist;
            return 1;
        }
    }
    return 0;
}

/* Ray (origin, unit direction) against a sphere: distance to the entry point, 0 when the origin is inside. */
s32 ColSphere_TestRay(CpSphere *sph, CpRay *ray, f32 *t, CpVec *pos) {
    CpVec d;
    f32 b;
    f32 c;
    f32 disc;

    Vec4_Sub(&d, &ray->origin, &sph->pos);
    b = Vec3_Dot(&d, &ray->dir);
    c = Vec3_Dot(&d, &d) - sph->radius * sph->radius;
    if (c > 0.0f && b > 0.0f) {
        return 0;
    }
    disc = b * b - c;
    if (disc < 0.0f) {
        return 0;
    }
    *t = -b - sqrtf(disc);
    if (*t < 0.0f) {
        *t = 0.0f;
    }
    pos->x = ray->origin.x + *t * ray->dir.x;
    pos->y = ray->origin.y + *t * ray->dir.y;
    pos->z = ray->origin.z + *t * ray->dir.z;
    pos->w = 1.0f;
    return 1;
}
