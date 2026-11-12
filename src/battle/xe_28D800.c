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


/*
 * 1 when a segment touches a box: separating axes (the box's three, then the three cross products with the
 * segment), touching counts as a hit. The cross tests add 100 * FLT_MIN (0x03C80000) to the absolute direction,
 * which is nothing in practice, so a zero-length segment is simply a point-in-box test. No caller.
 */
s32 ColBox_TestSegment(ColBox *box, ColSeg *seg) {
    ColVec center;
    ColVec half;
    ColVec mid;
    ColVec dir;
    f32 ax, ay, az;

    ColBox_GetCenter(box, &center);
    ColBox_GetHalf(box, &half);
    ColSeg_GetMidpoint(seg, &mid);
    Vec4_Sub(&dir, &seg->b, &mid);
    Vec4_Sub(&mid, &mid, &center);
    ax = __builtin_fabsf(dir.x);
    if (__builtin_fabsf(mid.x) > half.x + ax) {
        return 0;
    }
    ay = __builtin_fabsf(dir.y);
    if (__builtin_fabsf(mid.y) > half.y + ay) {
        return 0;
    }
    az = __builtin_fabsf(dir.z);
    if (__builtin_fabsf(mid.z) > half.z + az) {
        return 0;
    }
    ax += 1.175494351e-36f;
    ay += 1.175494351e-36f;
    az += 1.175494351e-36f;
    if (__builtin_fabsf(mid.y * dir.z - mid.z * dir.y) > half.y * az + half.z * ay) {
        return 0;
    }
    if (__builtin_fabsf(mid.z * dir.x - mid.x * dir.z) > half.x * az + half.z * ax) {
        return 0;
    }
    if (__builtin_fabsf(mid.x * dir.y - mid.y * dir.x) > half.x * ay + half.y * ax) {
        return 0;
    }
    return 1;
}

/* 1 when a tree node's box overlaps a box. */
s32 ColNode_TestBox(ColNode *node, ColBox *box) {
    return ColBox_Overlaps(box, &node->box) != 0;
}

/* Tree walk of ColMesh_CollectBox: appends the polygon index of every leaf whose box overlaps `box`. */
void ColMesh_CollectNode(ColNode *nodes, ColBox *box, s32 idx) {
    ColNode *node = &nodes[idx];

    if (ColNode_TestBox(node, box)) {
        if (ColNode_IsLeaf(node)) {
            if (gColWalkBuf != NULL) {
                if (gColWalkCount >= gColWalkMax) {
                    return;
                }
                gColWalkBuf[gColWalkCount] = node->left;
            }
            gColWalkCount++;
        } else {
            ColMesh_CollectNode(nodes, box, node->left);
            ColMesh_CollectNode(nodes, box, node->right);
        }
    }
}

/* Collects the polygon indices of a mesh whose leaf boxes overlap `box` (at most `max`); returns the count. */
s32 ColMesh_CollectBox(s32 max, u16 *buf, ColMesh *mesh, ColBox *box) {
    ColNode *nodes;

    if (mesh->nodeCount <= 0) {
        return 0;
    }
    nodes = (ColNode *)(gColMeshBase + mesh->nodeOfs);
    gColWalkMax = max;
    gColWalkBuf = buf;
    gColWalkCount = 0;
    ColMesh_CollectNode(nodes, box, 0);
    gColWalkBuf = NULL;
    return gColWalkCount;
}

/* Tree walk of ColMesh_WalkBox: calls the callback for every leaf whose box overlaps `box`. */
void ColMesh_WalkNode(ColNode *nodes, ColBox *box, s32 idx) {
    ColNode *node = &nodes[idx];

    if (ColNode_TestBox(node, box)) {
        if (ColNode_IsLeaf(node)) {
            s32 ret = gColWalkCb(node, gColWalkCtx);

            gColWalkCount |= ret;
            return;
        }
        ColMesh_WalkNode(nodes, box, node->left);
        ColMesh_WalkNode(nodes, box, node->right);
    }
}

/* Calls `cb(leaf, ctx)` for every leaf of a mesh whose box overlaps `box`; returns the OR of the results. */
s32 ColMesh_WalkBox(ColMesh *mesh, ColBox *box, void *ctx, ColMeshCb cb) {
    ColNode *nodes;

    if (mesh->nodeCount <= 0) {
        return 0;
    }
    if (cb == NULL) {
        return 0;
    }
    nodes = (ColNode *)(gColMeshBase + mesh->nodeOfs);
    gColWalkBox = box;
    gColWalkCb = cb;
    gColWalkCtx = ctx;
    gColWalkCount = 0;
    ColMesh_WalkNode(nodes, box, 0);
    return gColWalkCount;
}
