#include "common.h"
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


/*
 * 0x122698: rotates v about a unit axis (Rodrigues): v cos + (axis x v) sin + axis (axis . v)(1 - cos). The three
 * terms are full four-component vectors; w is then replaced by v->w, read AFTER out was written, so with out == v the
 * result's w is the sum's w.
 */
void Vec3_RotateAxis(Vec4 *out, Vec4 *v, Vec4 *axis, f32 angle) {
    Vec4 a;
    Vec4 b;
    Vec4 c;
    f32 cs;
    f32 sn;

    cs = Mathf_Cos(angle);
    sn = Mathf_Sin(angle);
    Vec4_Scale(&a, v, cs);
    Vec3_Cross(&b, axis, v);
    Vec4_Scale(&b, &b, sn);
    Vec4_Scale(&c, axis, Vec3_Dot(axis, v) * (1.0f - cs));
    Vec4_Add(out, &a, &b);
    Vec4_Add(out, out, &c);
    out->w = v->w;
}

/* 0x122790: rotates v about the X axis; same w behaviour as Vec3_RotateAxis. */
void Vec3_RotateX(Vec4 *out, Vec4 *v, f32 angle) {
    Vec4 a;
    Vec4 b;
    Vec4 c;
    f32 cs;
    f32 sn;

    cs = Mathf_Cos(angle);
    sn = Mathf_Sin(angle);
    Vec4_Scale(&a, v, cs);
    b.x = 0.0f;
    b.y = -v->z * sn;
    b.z = v->y * sn;
    b.w = 0.0f;
    c.x = v->x * (1.0f - cs);
    c.y = 0.0f;
    c.z = 0.0f;
    c.w = 0.0f;
    Vec4_Add(out, &a, &b);
    Vec4_Add(out, out, &c);
    out->w = v->w;
}

/* 0x122868: rotates v about the Y axis; same w behaviour as Vec3_RotateAxis. */
void Vec3_RotateY(Vec4 *out, Vec4 *v, f32 angle) {
    Vec4 a;
    Vec4 b;
    Vec4 c;
    f32 cs;
    f32 sn;

    cs = Mathf_Cos(angle);
    sn = Mathf_Sin(angle);
    Vec4_Scale(&a, v, cs);
    b.x = v->z * sn;
    b.y = 0.0f;
    b.z = -v->x * sn;
    b.w = 0.0f;
    c.x = 0.0f;
    c.y = v->y * (1.0f - cs);
    c.z = 0.0f;
    c.w = 0.0f;
    Vec4_Add(out, &a, &b);
    Vec4_Add(out, out, &c);
    out->w = v->w;
}
