#define Vu0Cur_RotateZXY func_00297828  /* fix_targets */ /* the original uses 0x297828 here */
#include "common.h"
#include "sys/math3d.h"

/*
 * Matrix builders of the vector / matrix library, 0x1204B8..0x120A80 (config/symbols/vu0_a.txt): the compiled C
 * part of Sony's libvu0 under the game's names. The two diagonal-scale routines in the middle are hand-written VU0
 * assembly in the original and are kept as top-level assembly (same bytes, checked by fdiff).
 * Portable reference versions are in src/port/vu0_a.c (bt3-port repository).
 */

extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_Translate(Mtx44 *dst, Mtx44 *src, Vec4 *v);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
extern void Mtx_Transpose(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_SetZeroW1(Vec4 *v);

/* dst = src rotated about Z by angles.z, then X by angles.x, then Y by angles.y (sceVu0RotMatrix). */
void Mtx_RotateZXY(Mtx44 *dst, Mtx44 *src, Vec4 *angles);

/* dst = src rotated about X by angles.x, then Y by angles.y, then Z by angles.z. */
void Mtx_RotateXYZ(Mtx44 *dst, Mtx44 *src, Vec4 *angles);

/* void Mtx_ScaleDiag(Mtx44 *dst, Mtx44 *src, Vec4 *v): dst = src with m[0][0] *= v.x, m[1][1] *= v.y, m[2][2] *= v.z.
 * Only the diagonal is multiplied: a scale only when the 3x3 part of src is diagonal. */


/* void Mtx_ScaleDiagUniform(Mtx44 *dst, Mtx44 *src, f32 s): the same with one factor. */


/* Mtx_RotateZXY into dst, then Mtx_Translate(dst, src, pos): the second call copies the rows of src again, so the
 * rotation survives only when dst == src (original bug; no callers). */
void Mtx_RotateZXYTranslate(Mtx44 *dst, Mtx44 *src, Vec4 *angles, Vec4 *pos);

/* World-to-view matrix of a camera at pos looking along zdir with ydir up (sceVu0CameraMatrix). */
void sceVu0CameraMatrix(Mtx44 *m, Vec4 *pos, Vec4 *zdir, Vec4 *ydir);

/* m = the four rows given (sceVu0LightColorMatrix: three light colours and the ambient colour). */
void sceVu0LightColorMatrix(Mtx44 *m, Vec4 *r0, Vec4 *r1, Vec4 *r2, Vec4 *r3);

/* m = transpose of the matrix whose rows are the normalised negated light directions (sceVu0NormalLightMatrix). */
void Mtx_MakeNormalLight(Mtx44 *m, Vec4 *l0, Vec4 *l1, Vec4 *l2);

/* View-to-screen matrix (sceVu0ViewScreenMatrix): perspective with projection distance scrz, scale (ax, ay),
 * centre (cx, cy) and the depth range [nearz, farz] mapped to [zmax, zmin]. */
void Mtx_MakeViewScreen(Mtx44 *m, f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 nearz, f32 farz);

/* Projection onto the plane a x + b y + c z = 1 from a point light at lp (mode != 0) or along the direction lp
 * (mode == 0) (sceVu0DropShadowMatrix). Plain FPU arithmetic. */
void Mtx_MakeDropShadow(Mtx44 *m, Vec4 *lp, f32 a, f32 b, f32 c, s32 mode);

/*
 * The current matrix (VU0 registers vf16-19) and its stack in VU0 data memory, 0x120A80..0x121008. Hand-written VU0
 * assembly in the original, kept as top-level assembly (same bytes, checked by fdiff); the compiled C functions
 * between them are C.
 */

extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Vec3_DirToEuler(Vec4 *out, Vec4 *dir);
extern Vec4 gVu0AxisZW; /* (0, 0, 1, 1) */

void Vu0Cur_Pop(void);
s32 Vu0Cur_GetStackDepth(void);
void Vu0Cur_StoreMtx(Mtx44 *m);
void Vu0Cur_Translate(Vec4 *v);
void Vu0Cur_RotateZ(f32 angle);
void Vu0Cur_RotateX(f32 angle);
void Vu0Cur_RotateY(f32 angle);

/* void Vu0Cur_Init(void): current matrix = identity built from vf0 (three vmr32), stack pointer vi15 = 0. */


/* void Vu0Cur_LoadIdentity(void): current matrix = identity (rows vf3, vf2, vf1, vf0). */


/* void Vu0Cur_Push(void): VU0 memory[vi15++] = row, for rows 0..3. */


/* void Vu0Cur_Pop(void): row = VU0 memory[--vi15], for rows 3..0. */


/* Pops n matrices; the current matrix ends as the last one popped. */
void Vu0Cur_PopN(s32 n);

/* void Vu0Cur_ResetStack(void): stack pointer vi15 = 0; the current matrix is untouched. */


/* Number of matrices on the stack: the stack pointer (a signed 16-bit count of rows) / 4. */
s32 Vu0Cur_GetStackDepth(void);

/* 1 when the stack is not empty. */
s32 Vu0Cur_IsStackUsed(void);

/* void Vu0Cur_LoadIdentityRot(void): rows 0-2 = identity, row 3 untouched. */


/* void Vu0Cur_ClearTrans(void): row 3 = (0, 0, 0, 1). */


/* void Vu0Cur_LoadMtx(Mtx44 *m): current matrix = m. */


/* void Vu0Cur_StoreMtx(Mtx44 *m): m = current matrix. */


/* void Vu0Cur_GetTrans(Vec4 *v): v = row 3. */


/* angles = Vec3_DirToEuler of the current matrix times (0, 0, 1, 1) = row 2 + row 3: unlike Mtx_AxisZToEuler the
 * translation is not removed first (original bug; no callers). */
void Vu0Cur_AxisZToEuler(Vec4 *angles);

/* void Vu0Cur_SetTrans(Vec4 *v): row 3 = v (all four components). */


/* void Vu0Cur_Translate(Vec4 *v): row 3 x, y, z += v. */


/* void Vu0Cur_TranslateLocal(Vec4 *v): row 3 = row0 * v.x + row1 * v.y + row2 * v.z + row3 * v.w. */


/* void Vu0Cur_MulMtx(Mtx44 *m): row[i] = sum over k of old row[k] * m[i][k] (Mtx_Mul(cur, cur, m)). */


/* void Vu0Cur_MulMtxRev(Mtx44 *m): row[i] = sum over k of m.row[k] * old row[i][k] (Mtx_Mul(cur, m, cur)). */


/* void Vu0Cur_Transpose(void). */


/* void Vu0Cur_InverseRT(void): Mtx_InverseRT on the current matrix. */


/* void Vu0Cur_RotateZ(f32 angle): Mtx_RotateZ on the current matrix. Keeps $ra in $a2 around Vu0_SinCos. */


/* void Vu0Cur_RotateX(f32 angle): Mtx_RotateX on the current matrix. */


/* void Vu0Cur_RotateY(f32 angle): Mtx_RotateY on the current matrix. */


/* Rotates the current matrix about Z by angles.z, then X by angles.x, then Y by angles.y. */
void Vu0Cur_RotateZXY(Vec4 *angles);

/* Rotates the current matrix about X, then Y, then Z. */
void Vu0Cur_RotateXYZ(Vec4 *angles);

/* void Vu0Cur_ScaleDiag(Vec4 *v): m[0][0] *= v.x, m[1][1] *= v.y, m[2][2] *= v.z (diagonal only). */


/* void Vu0Cur_ScaleDiagUniform(f32 s): the three diagonal elements *= s. */


/* Vu0Cur_RotateZXY(angles), then Vu0Cur_Translate(pos). */
void Vu0Cur_RotateZXYTranslate(Vec4 *angles, Vec4 *pos) {
    Vu0Cur_RotateZXY(angles);
    Vu0Cur_Translate(pos);
}

/* void Vu0Cur_MulVec4(Vec4 *out, Vec4 *v): out = row0 * v.x + row1 * v.y + row2 * v.z + row3 * v.w. */


/* void Vu0Cur_MulVec3(Vec4 *out, Vec4 *v): the same sum, x, y, z only; out.w = v.w. */

