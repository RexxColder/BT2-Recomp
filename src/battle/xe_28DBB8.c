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


/* 1 when |a - b| <= eps (0 when either is not a number). */
s32 Col_NearEq(f32 a, f32 b, f32 eps) {
    if (__builtin_fabsf(a - b) <= eps) {
        return 1;
    }
    return 0;
}

/*
 * Parameters of the closest points of two lines p1 + s d1 and p2 + t d2 with unit directions.
 * As built the two guards are inverted: a direction whose squared length IS within 1e-6 of 1 gives s = t = 0,
 * so the formula only runs for directions that are not unit length. Parallel lines (d1.d2 squared within 1e-6 of
 * 1, or larger) give 0, 0 too. Only called by ColObb_Contact.
 */
void Col_LineLineParams(f32 *s, f32 *t, ColVec *p1, ColVec *d1, ColVec *p2, ColVec *d2) {
    ColVec diff;
    f32 a;
    f32 b;
    f32 c;
    f32 den;
    f32 inv;

    if (Col_NearEq(Vec3_LengthSq(d1), 1.0f, 0.000001f)) {
        *s = 0.0f;
        *t = 0.0f;
        return;
    }
    if (Col_NearEq(Vec3_LengthSq(d2), 1.0f, 0.000001f)) {
        *s = 0.0f;
        *t = 0.0f;
        return;
    }
    Vec4_Sub(&diff, p2, p1);
    a = Vec3_Dot(&diff, d1);
    b = Vec3_Dot(&diff, d2);
    c = Vec3_Dot(d1, d2);
    den = c * c - 1.0f;
    if (den < -0.000001f) {
        inv = 1.0f / den;
        *s = (c * b - a) * inv;
        *t = (b - c * a) * inv;
    } else {
        *s = 0.0f;
        *t = 0.0f;
    }
}

/* 1 when two oriented boxes overlap or touch (the fifteen separating axes, no tolerance). */
s32 ColObb_Overlaps(ColObb *a, ColObb *b) {
    ColVec ha;
    ColVec hb;
    ColVec diff;
    ColMat3 R;
    ColMat3 absR;
    ColVec d;
    f32 t;
    f32 rb;
    f32 sum;
    f32 ra;

    Vec3_Copy(&ha, &a->half);
    Vec3_Copy(&hb, &b->half);
    Vec4_Sub(&diff, &a->center, &b->center);
    R.m[0][0] = Vec3_Dot(&a->axis[0], &b->axis[0]);
    R.m[0][1] = Vec3_Dot(&a->axis[0], &b->axis[1]);
    R.m[0][2] = Vec3_Dot(&a->axis[0], &b->axis[2]);
    d.x = Vec3_Dot(&a->axis[0], &diff);
    absR.m[0][0] = __builtin_fabsf(R.m[0][0]);
    absR.m[0][1] = __builtin_fabsf(R.m[0][1]);
    absR.m[0][2] = __builtin_fabsf(R.m[0][2]);
    t = __builtin_fabsf(d.x);
    rb = hb.x * absR.m[0][0] + hb.y * absR.m[0][1] + hb.z * absR.m[0][2];
    sum = ha.x + rb;
    if (t > sum) {
        return 0;
    }
    R.m[1][0] = Vec3_Dot(&a->axis[1], &b->axis[0]);
    R.m[1][1] = Vec3_Dot(&a->axis[1], &b->axis[1]);
    R.m[1][2] = Vec3_Dot(&a->axis[1], &b->axis[2]);
    d.y = Vec3_Dot(&a->axis[1], &diff);
    absR.m[1][0] = __builtin_fabsf(R.m[1][0]);
    absR.m[1][1] = __builtin_fabsf(R.m[1][1]);
    absR.m[1][2] = __builtin_fabsf(R.m[1][2]);
    t = __builtin_fabsf(d.y);
    rb = hb.x * absR.m[1][0] + hb.y * absR.m[1][1] + hb.z * absR.m[1][2];
    sum = ha.y + rb;
    if (t > sum) {
        return 0;
    }
    R.m[2][0] = Vec3_Dot(&a->axis[2], &b->axis[0]);
    R.m[2][1] = Vec3_Dot(&a->axis[2], &b->axis[1]);
    R.m[2][2] = Vec3_Dot(&a->axis[2], &b->axis[2]);
    d.z = Vec3_Dot(&a->axis[2], &diff);
    absR.m[2][0] = __builtin_fabsf(R.m[2][0]);
    absR.m[2][1] = __builtin_fabsf(R.m[2][1]);
    absR.m[2][2] = __builtin_fabsf(R.m[2][2]);
    t = __builtin_fabsf(d.z);
    rb = hb.x * absR.m[2][0] + hb.y * absR.m[2][1] + hb.z * absR.m[2][2];
    sum = ha.z + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(Vec3_Dot(&b->axis[0], &diff));
    ra = ha.x * absR.m[0][0] + ha.y * absR.m[1][0] + ha.z * absR.m[2][0];
    sum = ra + hb.x;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(Vec3_Dot(&b->axis[1], &diff));
    ra = ha.x * absR.m[0][1] + ha.y * absR.m[1][1] + ha.z * absR.m[2][1];
    sum = ra + hb.y;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(Vec3_Dot(&b->axis[2], &diff));
    ra = ha.x * absR.m[0][2] + ha.y * absR.m[1][2] + ha.z * absR.m[2][2];
    sum = ra + hb.z;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.z * R.m[1][0] - d.y * R.m[2][0]);
    ra = ha.y * absR.m[2][0] + ha.z * absR.m[1][0];
    rb = hb.y * absR.m[0][2] + hb.z * absR.m[0][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.z * R.m[1][1] - d.y * R.m[2][1]);
    ra = ha.y * absR.m[2][1] + ha.z * absR.m[1][1];
    rb = hb.x * absR.m[0][2] + hb.z * absR.m[0][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.z * R.m[1][2] - d.y * R.m[2][2]);
    ra = ha.y * absR.m[2][2] + ha.z * absR.m[1][2];
    rb = hb.x * absR.m[0][1] + hb.y * absR.m[0][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.x * R.m[2][0] - d.z * R.m[0][0]);
    ra = ha.x * absR.m[2][0] + ha.z * absR.m[0][0];
    rb = hb.y * absR.m[1][2] + hb.z * absR.m[1][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.x * R.m[2][1] - d.z * R.m[0][1]);
    ra = ha.x * absR.m[2][1] + ha.z * absR.m[0][1];
    rb = hb.x * absR.m[1][2] + hb.z * absR.m[1][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.x * R.m[2][2] - d.z * R.m[0][2]);
    ra = ha.x * absR.m[2][2] + ha.z * absR.m[0][2];
    rb = hb.x * absR.m[1][1] + hb.y * absR.m[1][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.y * R.m[0][0] - d.x * R.m[1][0]);
    ra = ha.x * absR.m[1][0] + ha.y * absR.m[0][0];
    rb = hb.y * absR.m[2][2] + hb.z * absR.m[2][1];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.y * R.m[0][1] - d.x * R.m[1][1]);
    ra = ha.x * absR.m[1][1] + ha.y * absR.m[0][1];
    rb = hb.x * absR.m[2][2] + hb.z * absR.m[2][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    t = __builtin_fabsf(d.y * R.m[0][2] - d.x * R.m[1][2]);
    ra = ha.x * absR.m[1][2] + ha.y * absR.m[0][2];
    rb = hb.x * absR.m[2][1] + hb.y * absR.m[2][0];
    sum = ra + rb;
    if (t > sum) {
        return 0;
    }
    return 1;
}
