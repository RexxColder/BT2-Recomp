#include "common.h"
/* BT2 targets of these calls / globals (checked against the original relocations). */
#define Mtx_MulVec4 func_00129C50
#include "sys/math3d.h"
#include "sys/mathf.h"
#include "sys/randf.h"

/*
 * The whole second half of the vector / matrix library, 0x121008..0x122940, in address order with no gap.
 *
 * 25 functions are compiled C. The other 67 are hand-written VU0 assembly in the original and are kept as top-level
 * assembly blocks (same bytes, checked by fdiff), as in src/sys/vu0_a_c*.c; three of them use encodings the
 * disassembler does not know and are written as words. src/port/vu0_b.c (bt3-port repository) has the exact portable equivalent of every
 * routine.
 */

/* The polygon clipper's vertex: position, texture coordinate, colour. */
typedef struct ClipVtx {
    /* 0x00 */ Vec4 pos;
    /* 0x10 */ Vec4 uv;
    /* 0x20 */ Vec4 col;
} ClipVtx; /* size 0x30 */

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern s32 memcmp(const void *a, const void *b, u32 n);
extern void Rand_Init(void);

/* First half of the library (config/symbols/vu0_a.txt). */
extern void Vu0_InitAxisRegs(void);                /* vf1-3 = unit vectors */
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_RotateZXY(Mtx44 *out, const Mtx44 *m, Vec4 *angles); /* out = m rotated by Euler angles */
extern void Vu0Cur_Init(void);                /* current matrix = identity, stack pointer = 0 */
extern void Vu0Cur_LoadIdentity(void);                /* current matrix = identity */
extern void Vu0Cur_Push(void);                /* push the current matrix */
extern void Vu0Cur_Pop(void);                /* pop the current matrix */
extern void Vu0Cur_ResetStack(void);                /* stack pointer = 0 */
extern s32 Vu0Cur_IsStackUsed(void);                 /* stack depth != 0 */
extern void Vu0Cur_LoadMtx(Mtx44 *m);            /* current matrix = m */
extern void Vu0Cur_RotateZXY(Vec4 *angles);        /* rotates the current matrix by Euler angles */
extern void Vu0Cur_MulVec4(void *out, void *v);  /* out = current matrix * v, four components */
extern void Vu0Cur_MulVec3(void *out, void *v);  /* the same, x, y, z only */

/* Assembly routines of this half. */
extern void Vu0View_LoadMtx(Mtx44 *m);
extern void Vu0View_StoreMtx(Mtx44 *m);
extern void ClipVtx_Copy(ClipVtx *dst, ClipVtx *src);
extern void ClipVtx_CopyArray(ClipVtx *dst, ClipVtx *src, s32 n);
extern void ClipVtx_Lerp(ClipVtx *out, ClipVtx *a, ClipVtx *b, f32 t);
extern f32 ClipPlane_EdgeParam(Vec4 *plane, ClipVtx *a, ClipVtx *b, f32 dist);
extern void ClipPlane_DistArray(Vec4 *dist, ClipVtx *poly, Vec4 *plane, s32 n);
extern void Mtx_MulVec3(void *out, Mtx44 *m, Vec4 *v);
extern void Mtx_MulVec4(Vec4 *out, Mtx44 *m, Vec4 *v);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Cross(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec4_Add(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *out, Vec4 *v, f32 s);

extern const Mtx44 D_002EC260; /* the identity matrix */
extern f32 D_002FC32C;         /* 0.1234141f, the boot seed */

void Vec3_Set(Vec4 *v, f32 x, f32 y, f32 z);
void Vec3_DirToEuler(Vec4 *out, Vec4 *dir);

/* 0x121008: out = (identity rotated by the Euler angles) * v, through the current matrix, which is not restored. */
void Vu0Cur_RotEulerMulVec4(Vec4 *out, Vec4 *angles, Vec4 *v);

/* 0x121058: the same, writing x, y, z only. */
void Vu0Cur_RotEulerMulVec3(Vec4 *out, Vec4 *angles, Vec4 *v);

/* 0x1210A8..0x1214A0: Vu0Cur_Project*, Vu0Clip_*, Vu0Screen_*, Vu0View_*Mtx. */

/* 0x1210A8: Vu0Cur_ProjectInt, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Cur_ProjectInt in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1210D8: Vu0Cur_ProjectPoint, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Cur_ProjectPoint in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121140: Vu0Cur_ProjectPoints, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Cur_ProjectPoints in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1211C8: Vu0Cur_ProjectPointStq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Cur_ProjectPointStq in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121240: Vu0Cur_ProjectPointsStq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Cur_ProjectPointsStq in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1212D8: Vu0Clip_LoadMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Clip_LoadMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1212F0: Vu0Clip_StoreMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Clip_StoreMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121308: Vu0Clip_SetMulMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Clip_SetMulMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121370: Vu0Screen_LoadMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Screen_LoadMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121388: Vu0Screen_StoreMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Screen_StoreMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1213A0: Vu0Screen_SetMulMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0Screen_SetMulMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121408: Vu0View_LoadMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0View_LoadMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121420: Vu0View_StoreMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0View_StoreMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121438: Vu0View_SetMulMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vu0View_SetMulMtx in src/port/vu0_b.c (bt3-port repository)). */



/* 0x1214A0: vf28-31 = rotation X, Z, Y (libm sinf / cosf) with row 3 = rotation * trans. */
void Vu0View_SetRotTrans(Vec4 *rot, Vec4 *trans);

/* 0x121640: vf28-31: row 3 = M * trans, then rotations Y, Z, X applied. No callers. */
void Vu0View_ApplyTransRot(Vec4 *rot, Vec4 *trans);

/*
 * Two rows of a rotation matrix through the current matrix (vf16-19): ra = cur * a, rb = cur * b, then the two results
 * replace two rows of the current matrix.
 */
#define VU0_CUR_MUL2(a, b, ra, rb, da, db) \
    __asm__ volatile( \
        "lqc2 $vf8, %0\n" \
        "lqc2 $vf9, %1\n" \
        "vmulax.xyzw $ACC, $vf16, $vf8x\n" \
        "vmadday.xyzw $ACC, $vf17, $vf8y\n" \
        "vmaddaz.xyzw $ACC, $vf18, $vf8z\n" \
        "vmaddw.xyzw " ra ", $vf19, $vf8w\n" \
        "vmulax.xyzw $ACC, $vf16, $vf9x\n" \
        "vmadday.xyzw $ACC, $vf17, $vf9y\n" \
        "vmaddaz.xyzw $ACC, $vf18, $vf9z\n" \
        "vmaddw.xyzw " rb ", $vf19, $vf9w\n" \
        "vmove.xyzw " da ", $vf7\n" \
        "vmove.xyzw " db ", $vf4\n" \
        : : "m"(a), "m"(b))

/*
 * 0x1217D0: current matrix = current * Ry(rot.y) * Rx(rot.x) * Rz(rot.z), each rotation applied to the two rows it
 * changes; libm cosf / sinf. Compiled C with inline VU0 assembly.
 */
void Vu0Cur_RotateYXZ(Vec4 *rot);

/* 0x121910..0x121950: eight empty functions, no callers. */
void Vu0_Stub0(void);

void Vu0_Stub1(void);

void Vu0_Stub2(void);

void Vu0_Stub3(void);

void Vu0_Stub4(void);

void Vu0_Stub5(void);

void Vu0_Stub6(void);

void Vu0_Stub7(void);

/* 0x121950..0x121A10: ClipVtx_Set, ClipVtx_Copy, ClipVtx_SetArray, ClipVtx_CopyArray. */

/* 0x121950: ClipVtx_Set, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipVtx_Set in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121970: ClipVtx_Copy, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipVtx_Copy in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121990: ClipVtx_SetArray, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipVtx_SetArray in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1219D8: ClipVtx_CopyArray, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipVtx_CopyArray in src/port/vu0_b.c (bt3-port repository)). */



/*
 * 0x121A10: clips a convex polygon of n vertices (at most 9 in, 9 out) against one plane, in place, and returns the
 * new vertex count. A vertex is outside when dot(plane.xyz, pos) + plane.w < 0. Each edge that crosses the plane gets
 * a vertex at t = dist(cur) / dot(plane, cur - next), interpolated as next * t + cur * (1 - t) on all three quadwords.
 */
s32 ClipPoly_ClipPlane(ClipVtx *poly, Vec4 *plane, s32 n);

/* 0x121C18..0x121DA8: ClipVtx_Lerp, ClipPlane_EdgeParam, ClipPlane_DistArray, ClipPoly_ProjectMtx / Cur. */

/* 0x121C18: ClipVtx_Lerp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipVtx_Lerp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121C68: ClipPlane_EdgeParam, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipPlane_EdgeParam in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121C98: ClipPlane_DistArray, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipPlane_DistArray in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121CD8: ClipPoly_ProjectMtx, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipPoly_ProjectMtx in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121D48: ClipPoly_ProjectCur, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_ClipPoly_ProjectCur in src/port/vu0_b.c (bt3-port repository)). */



/* 0x121DA8: boot-time set-up of the VU0 state and of both random generators. */
void Vu0_Init(void);

/* 0x121DE0: the remains of an assert: compares a stored identity with the constant one and reads the stack depth. */
void Vu0_CheckState(void);

/* 0x121E18..0x121E28: Vec4_SetZeroW1, Vec4_SetZero. */

/* 0x121E18: Vec4_SetZeroW1, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_SetZeroW1 in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121E20: Vec4_SetZero, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_SetZero in src/port/vu0_b.c (bt3-port repository)). */



/* 0x121E28: v = (x, y, z, w). */
void Vec4_Set(Vec4 *v, f32 x, f32 y, f32 z, f32 w);

/* 0x121E40: sets x, y, z and leaves w. */
void Vec3_Set(Vec4 *v, f32 x, f32 y, f32 z);

/* 0x121E50..0x122030: Vec3_Normalize .. Mtx_MulVec3. */

/* 0x121E50: Vec3_Normalize, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Normalize in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121E90: Vec4_Swap, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Swap in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121EA8: Vec4_Add, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Add in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121EC0: Vec3_Add, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Add in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121ED8: Vec4_Sub, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Sub in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121EF0: Vec3_Sub, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Sub in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F08: Vec4_Mul, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Mul in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F20: Vec3_Mul, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Mul in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F38: Vec4_Scale, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Scale in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F50: Vec3_Scale, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Scale in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F68: Vec4_Div, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Div in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121F88: Vec3_Div, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Div in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121FA8: Vec4_Copy, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Copy in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121FB8: Vec3_Copy, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Copy in src/port/vu0_b.c (bt3-port repository)). */


/* 0x121FD0: Mtx_MulVec4, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_MulVec4 in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122000: Mtx_MulVec3, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_MulVec3 in src/port/vu0_b.c (bt3-port repository)). */



/* 0x122030: out = (identity rotated by the Euler angles) * v, all four components. */
void Vec4_RotateEuler(Vec4 *out, Vec4 *angles, Vec4 *v) {
    Mtx44 m;

    Mtx_RotateZXY(&m, &D_002EC260, angles);
    Mtx_MulVec4(out, &m, v);
}

/* 0x122088..0x122258: Vec3_Dot .. Vec3_DistSq. */

/* 0x122088: Vec3_Dot, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Dot in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1220B0: Vec3_Cross, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Cross in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1220D0: Vec4_ToFixed12, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_ToFixed12 in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1220E0: Vec4_ToFixed4, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_ToFixed4 in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1220F0: Vec4_ToInt, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_ToInt in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122100: Vec4_ToFixed4XY, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_ToFixed4XY in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122118: Vec4_Clamp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Clamp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122140: Vec3_Clamp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Clamp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122168: Vec4_Lerp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_Lerp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122190: Vec3_Lerp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Lerp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1221B8: Vec3_Length, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Length in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1221E0: Vec3_LengthSq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_LengthSq in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122200: Vec3_Dist, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Dist in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122230: Vec3_DistSq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_DistSq in src/port/vu0_b.c (bt3-port repository)). */



/* 0x122258: yaw and pitch of a direction: out = (-atan2f(y, length(x, 0, z)), atan2f(x, z), 0); out.w is left. */
void Vec3_DirToEuler(Vec4 *out, Vec4 *dir);

/* 0x1222D8: Vec3_DirToEuler of a - b. No callers. */
void Vec3_DiffToEuler(Vec4 *out, Vec4 *a, Vec4 *b);

/* 0x122310..0x122588: Mtx_Project*. */

/* 0x122310: Mtx_ProjectInt, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_ProjectInt in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122350: Mtx_ProjectPoint, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_ProjectPoint in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1223C8: Mtx_ProjectPoints, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_ProjectPoints in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122458: Mtx_ProjectPointStq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_ProjectPointStq in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1224E0: Mtx_ProjectPointsStq, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Mtx_ProjectPointsStq in src/port/vu0_b.c (bt3-port repository)). */



/* 0x122588: empty, no callers. */
void Vu0_Stub8(void);

/* 0x122590..0x122698: Vec3_AddSub .. Vec3_AddClamp. */

/* 0x122590: Vec3_AddSub, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_AddSub in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1225B0: Vec3_SubAdd, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_SubAdd in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1225D0: Vec3_ScaleAdd, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_ScaleAdd in src/port/vu0_b.c (bt3-port repository)). */


/* 0x1225F0: Vec3_ScaleSub, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_ScaleSub in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122610: Vec3_Add4, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_Add4 in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122638: Vec4_AddClamp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec4_AddClamp in src/port/vu0_b.c (bt3-port repository)). */


/* 0x122668: Vec3_AddClamp, hand-written VU0 assembly in the original (described in config/symbols/vu0_b.txt; C reference
 * Ref_Vec3_AddClamp in src/port/vu0_b.c (bt3-port repository)). */



/*
 * 0x122698: rotates v about a unit axis (Rodrigues): v cos + (axis x v) sin + axis (axis . v)(1 - cos). The three
 * terms are full four-component vectors; w is then replaced by v->w, read AFTER out was written, so with out == v the
 * result's w is the sum's w.
 */
void Vec3_RotateAxis(Vec4 *out, Vec4 *v, Vec4 *axis, f32 angle);

/* 0x122790: rotates v about the X axis; same w behaviour as Vec3_RotateAxis. */
void Vec3_RotateX(Vec4 *out, Vec4 *v, f32 angle);

/* 0x122868: rotates v about the Y axis; same w behaviour as Vec3_RotateAxis. */
void Vec3_RotateY(Vec4 *out, Vec4 *v, f32 angle);
