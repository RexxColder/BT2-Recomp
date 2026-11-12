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


/* Places an oriented box: copies the matrix, then takes the axes, the centre and the world corners from it. */
void ColObb_Update(ColObb *obb, void *mtx) {
    Mtx_Copy(obb->mtx, mtx);
    obb->axis[0].x = obb->mtx[0][0];
    obb->axis[0].y = obb->mtx[0][1];
    obb->axis[0].z = obb->mtx[0][2];
    obb->axis[1].x = obb->mtx[1][0];
    obb->axis[1].y = obb->mtx[1][1];
    obb->axis[1].z = obb->mtx[1][2];
    obb->axis[2].x = obb->mtx[2][0];
    obb->axis[2].y = obb->mtx[2][1];
    obb->axis[2].z = obb->mtx[2][2];
    obb->center.x = obb->mtx[3][0];
    obb->center.y = obb->mtx[3][1];
    obb->center.z = obb->mtx[3][2];
    Mtx_MulVec4(&obb->world[0], obb->mtx, &obb->local[0]);
    Mtx_MulVec4(&obb->world[1], obb->mtx, &obb->local[1]);
    Mtx_MulVec4(&obb->world[2], obb->mtx, &obb->local[2]);
    Mtx_MulVec4(&obb->world[3], obb->mtx, &obb->local[3]);
    Mtx_MulVec4(&obb->world[4], obb->mtx, &obb->local[4]);
    Mtx_MulVec4(&obb->world[5], obb->mtx, &obb->local[5]);
    Mtx_MulVec4(&obb->world[6], obb->mtx, &obb->local[6]);
    Mtx_MulVec4(&obb->world[7], obb->mtx, &obb->local[7]);
}
