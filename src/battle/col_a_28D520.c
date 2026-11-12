/*
 * Collision primitives: 0x230B38..0x236190 (include/battle/col_a.h has the layouts and the contracts).
 *
 * The object really starts one function earlier: StgAabb_SetEmpty (0x230B10, at the end of stg_d.c) is the first
 * of the box helpers and owns the constant in front of this file's pool (0x2FE3F0, 1e10).
 *
 * In address order:
 *   0x230B38  axis-aligned box helpers (ColBox_*)
 *   0x230E88  collision mesh: tree node tests, polygon and vertex access, base pointer
 *   0x230F70  oriented box set-up (ColObb_Init / ColObb_Update)
 *   0x231148  box against box, ray against box, segment against box
 *   0x231590  the two walks of a mesh's box tree (collect indices / callback per leaf)
 *   0x2317C0  Col_NearEq, Col_LineLineParams
 *   0x231930  oriented box against oriented box (ColObb_Overlaps)
 *   0x231F38  ColObb_Contact (dead code, left in assembly)
 *
 * Everything here is compiled C on the FPU; no function contains VU0 code. The vector helpers it CALLS are
 * hand-written VU0 routines (Vec4_Copy, Vec4_Sub, Vec3_Dot, Mtx_MulVec4, Vec3_Copy, Vec3_LengthSq,
 * Vec3_Normalize): see the header for what that means for a port.
 *
 * SIMULATION: all of it is pure geometry called by the stage collision (eft_det_b.c), the hit detection
 * (eft_det_a.c), the camera and the battle objects. No random draw, no pad or screen input, no time.
 * The only state is the mesh base pointer and the walk variables (gColWalk*), which make the two mesh walks
 * non re-entrant: a callback must not start another walk.
 */
#include "common.h"
#include "battle/col_a.h"

extern void Vec4_Copy(ColVec *dst, ColVec *src);
extern void Vec4_Sub(ColVec *dst, ColVec *a, ColVec *b);
extern void Mtx_MulVec4(ColVec *dst, void *mtx, ColVec *v);
extern f32 Vec3_Dot(ColVec *a, ColVec *b);
extern void Mtx_Copy(void *dst, void *src);      /* copies a 4x4 matrix (128-bit moves) */
extern void Vec3_Copy(ColVec *dst, ColVec *src);  /* copies x, y, z and leaves w (VU0) */
extern f32 Vec3_LengthSq(ColVec *v);                  /* squared length of x, y, z (VU0) */
extern void ColSeg_GetMidpoint(ColSeg *seg, ColVec *out);  /* middle of a segment, w = 1 */

/* Sets a box from its centre and half extents. */
void ColBox_SetCenterHalf(ColBox *box, ColVec *center, ColVec *half);

/* Grows a box to contain a point; also sets the point's w to 1. */
void ColBox_AddPoint(ColBox *box, ColVec *pt);

/* Grows a box to contain a point, leaving the point alone. */
void ColBox_AddPointKeepW(ColBox *box, ColVec *pt);

/* Centre of a box: (max + min) * 0.5, w = 1. */
void ColBox_GetCenter(ColBox *box, ColVec *out);

/* Half extents of a box: (max - min) * 0.5, w = 1. */
void ColBox_GetHalf(ColBox *box, ColVec *out);

/* Size of a box: max - min, w = 1. No caller. */
void ColBox_GetSize(ColBox *box, ColVec *out);

/* 1 when the box is at least 1e-6 thick on every axis (max >= min + 1e-6); an empty box gives 0. No caller. */
s32 ColBox_HasVolume(ColBox *box);

/* 1 when the point is inside the box, faces included. */
s32 ColBox_ContainsPoint(ColBox *box, ColVec *pt);

/* 1 when the tree node is a leaf (no second child). */
s32 ColNode_IsLeaf(ColNode *node);

/* 1 when the tree node is a leaf without a polygon. No caller. */
s32 ColNode_IsEmptyLeaf(ColNode *node);

/* Copies the three corners of a polygon out of the mesh's vertex array. */
void ColMesh_GetPolyVerts(ColMesh *mesh, ColPoly *poly, ColVec *v0, ColVec *v1, ColVec *v2);

/* Polygon `idx` of a mesh. */
ColPoly *ColMesh_GetPoly(ColMesh *mesh, s32 idx);

/* Sets the base the mesh offsets are counted from (the stage's collision block). */
void ColMesh_SetBase(s32 *base);

/* Sets up an oriented box from a centre and three half extents: the eight local corners. */
void ColObb_Init(ColObb *obb, ColVec *center, f32 hx, f32 hy, f32 hz);

/* Places an oriented box: copies the matrix, then takes the axes, the centre and the world corners from it. */
void ColObb_Update(ColObb *obb, void *mtx);

/* 1 when two boxes overlap or touch. */
s32 ColBox_Overlaps(ColBox *a, ColBox *b) {
    s32 ret = 0;

    if (!(a->min[0] > b->max[0]) && !(a->max[0] < b->min[0]) && !(a->min[1] > b->max[1]) &&
        !(a->max[1] < b->min[1]) && !(a->min[2] > b->max[2]) && !(a->max[2] < b->min[2])) {
        ret = 1;
    }
    return ret;
}

/*
 * Where a ray enters a box (Woo's method, "Fast Ray-Box Intersection"). Returns 1 and the entry point, or 1 and
 * the origin itself (w = 1) when the origin is inside or on the box. The ray is unbounded: `dir` is not
 * normalised and a hit beyond origin + dir still counts. The entry point may miss the face by 0.001 per axis.
 * A zero direction component on an axis where the origin is outside gives t = -1 for that axis (never chosen
 * over a real candidate); a ray that starts outside and points away gives 0. `out->w` is only written for the
 * inside case. Ties between candidate planes go to the lower axis (x, then y, then z).
 */
s32 ColBox_ClipRay(ColBox *box, ColRay *ray, ColVecA *out);

/*
 * 1 when a segment touches a box: separating axes (the box's three, then the three cross products with the
 * segment), touching counts as a hit. The cross tests add 100 * FLT_MIN (0x03C80000) to the absolute direction,
 * which is nothing in practice, so a zero-length segment is simply a point-in-box test. No caller.
 */
s32 ColBox_TestSegment(ColBox *box, ColSeg *seg);

/* 1 when a tree node's box overlaps a box. */
s32 ColNode_TestBox(ColNode *node, ColBox *box);

/* Tree walk of ColMesh_CollectBox: appends the polygon index of every leaf whose box overlaps `box`. */
void ColMesh_CollectNode(ColNode *nodes, ColBox *box, s32 idx);

/* Collects the polygon indices of a mesh whose leaf boxes overlap `box` (at most `max`); returns the count. */
s32 ColMesh_CollectBox(s32 max, u16 *buf, ColMesh *mesh, ColBox *box);

/* Tree walk of ColMesh_WalkBox: calls the callback for every leaf whose box overlaps `box`. */
void ColMesh_WalkNode(ColNode *nodes, ColBox *box, s32 idx);

/* Calls `cb(leaf, ctx)` for every leaf of a mesh whose box overlaps `box`; returns the OR of the results. */
s32 ColMesh_WalkBox(ColMesh *mesh, ColBox *box, void *ctx, ColMeshCb cb);

/* 1 when |a - b| <= eps (0 when either is not a number). */
s32 Col_NearEq(f32 a, f32 b, f32 eps);

/*
 * Parameters of the closest points of two lines p1 + s d1 and p2 + t d2 with unit directions.
 * As built the two guards are inverted: a direction whose squared length IS within 1e-6 of 1 gives s = t = 0,
 * so the formula only runs for directions that are not unit length. Parallel lines (d1.d2 squared within 1e-6 of
 * 1, or larger) give 0, 0 too. Only called by ColObb_Contact.
 */
void Col_LineLineParams(f32 *s, f32 *t, ColVec *p1, ColVec *d1, ColVec *p2, ColVec *d2);

/* 1 when two oriented boxes overlap or touch (the fifteen separating axes, no tolerance). */
s32 ColObb_Overlaps(ColObb *a, ColObb *b);

/*
 * Contact between two oriented boxes: least-penetration axis, then a contact normal and point. 0 when the boxes
 * are apart. NO CALLER anywhere in the game (dead code), and it does not do what it was meant to:
 *   - the nine edge-edge axes are only considered when two ways of computing the same quantity DISAGREE by more
 *     than 1e-6 (an inverted check, like the one in Col_LineLineParams), and the first of them never is;
 *   - Col_LineLineParams returns 0, 0 for unit axes, so an edge contact is just the chosen corner of box a.
 * Left in assembly (0x4258 bytes, a nine-way jump table at 0x2F2170 whose cases are written out by hand).
 * What differs in the attempt below: it folds the nine edge cases into one indexed block, so it produces no jump
 * table and a different frame; only the fifteen-axis search and the two face cases follow the original's shape.
 */
#if 0
extern f32 D_002FEBA8[];     /* 0x2FEBA8: FLT_MAX (initialised data, reached with lui / lwc1, so not a small extern) */
extern f32 sqrtf(f32 x);
extern void Vec3_Normalize(ColVec *dst, ColVec *src);

#define COL_AXIS_KEEP(code_)   \
    if (d < 0.0f) {            \
        return 0;              \
    }                          \
    if (d < *depth) {          \
        *depth = d;            \
        code = (code_);        \
    }

s32 ColObb_Contact(ColObb *a, ColObb *b, ColVec *normal, ColVec *point, f32 *depth);
#endif

