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
void ColBox_SetCenterHalf(ColBox *box, ColVec *center, ColVec *half) {
    box->min[0] = center->x - half->x;
    box->min[1] = center->y - half->y;
    box->min[2] = center->z - half->z;
    box->max[0] = center->x + half->x;
    box->max[1] = center->y + half->y;
    box->max[2] = center->z + half->z;
}

/* Grows a box to contain a point; also sets the point's w to 1. */
void ColBox_AddPoint(ColBox *box, ColVec *pt) {
    if (pt->x < box->min[0]) {
        box->min[0] = pt->x;
    }
    if (box->max[0] < pt->x) {
        box->max[0] = pt->x;
    }
    if (pt->y < box->min[1]) {
        box->min[1] = pt->y;
    }
    if (box->max[1] < pt->y) {
        box->max[1] = pt->y;
    }
    if (pt->z < box->min[2]) {
        box->min[2] = pt->z;
    }
    if (box->max[2] < pt->z) {
        box->max[2] = pt->z;
    }
    pt->w = 1.0f;
}

/* Grows a box to contain a point, leaving the point alone. */
void ColBox_AddPointKeepW(ColBox *box, ColVec *pt) {
    if (pt->x < box->min[0]) {
        box->min[0] = pt->x;
    }
    if (box->max[0] < pt->x) {
        box->max[0] = pt->x;
    }
    if (pt->y < box->min[1]) {
        box->min[1] = pt->y;
    }
    if (box->max[1] < pt->y) {
        box->max[1] = pt->y;
    }
    if (pt->z < box->min[2]) {
        box->min[2] = pt->z;
    }
    if (box->max[2] < pt->z) {
        box->max[2] = pt->z;
    }
}

/* Centre of a box: (max + min) * 0.5, w = 1. */
void ColBox_GetCenter(ColBox *box, ColVec *out) {
    out->x = (box->max[0] + box->min[0]) * 0.5f;
    out->y = (box->max[1] + box->min[1]) * 0.5f;
    out->z = (box->max[2] + box->min[2]) * 0.5f;
    out->w = 1.0f;
}

/* Half extents of a box: (max - min) * 0.5, w = 1. */
void ColBox_GetHalf(ColBox *box, ColVec *out) {
    out->x = (box->max[0] - box->min[0]) * 0.5f;
    out->y = (box->max[1] - box->min[1]) * 0.5f;
    out->z = (box->max[2] - box->min[2]) * 0.5f;
    out->w = 1.0f;
}

/* Size of a box: max - min, w = 1. No caller. */
void ColBox_GetSize(ColBox *box, ColVec *out) {
    out->x = box->max[0] - box->min[0];
    out->y = box->max[1] - box->min[1];
    out->z = box->max[2] - box->min[2];
    out->w = 1.0f;
}

/* 1 when the box is at least 1e-6 thick on every axis (max >= min + 1e-6); an empty box gives 0. No caller. */
s32 ColBox_HasVolume(ColBox *box) {
    if (box->max[0] < box->min[0] + 0.000001f || box->max[1] < box->min[1] + 0.000001f ||
        box->max[2] < box->min[2] + 0.000001f) {
        return 0;
    }
    return 1;
}

/* 1 when the point is inside the box, faces included. */
s32 ColBox_ContainsPoint(ColBox *box, ColVec *pt) {
    s32 ret = 0;

    if (!(box->max[0] < pt->x) && !(pt->x < box->min[0]) && !(box->max[1] < pt->y) && !(pt->y < box->min[1]) &&
        !(box->max[2] < pt->z) && !(pt->z < box->min[2])) {
        ret = 1;
    }
    return ret;
}

/* 1 when the tree node is a leaf (no second child). */
s32 ColNode_IsLeaf(ColNode *node) {
    return node->right == -1;
}

/* 1 when the tree node is a leaf without a polygon. No caller. */
s32 ColNode_IsEmptyLeaf(ColNode *node) {
    s32 ret = 0;

    if (node->right == -1) {
        ret = node->left == -1;
    }
    return ret;
}

/* Copies the three corners of a polygon out of the mesh's vertex array. */
void ColMesh_GetPolyVerts(ColMesh *mesh, ColPoly *poly, ColVec *v0, ColVec *v1, ColVec *v2) {
    ColVec *vtx = (ColVec *)(gColMeshBase + mesh->vtxOfs);

    Vec4_Copy(v0, &vtx[poly->vtx[0]]);
    Vec4_Copy(v1, &vtx[poly->vtx[1]]);
    Vec4_Copy(v2, &vtx[poly->vtx[2]]);
}

/* Polygon `idx` of a mesh. */
ColPoly *ColMesh_GetPoly(ColMesh *mesh, s32 idx) {
    ColPoly *polys;

    polys = (ColPoly *)(gColMeshBase + mesh->polyOfs);
    return polys + idx;
}
