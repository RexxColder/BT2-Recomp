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

/* 0x293BE0: squared length of a vector (x*x + y*y + z*z), hand-written VU0 code kept inside this module
   (BT3 calls the shared Vec3_LengthSq instead). */
#ifdef __mips__
__asm__(
    ".text\n"
    ".align 3\n"
    ".globl ColB_Vec3LengthSq\n"
    ".type ColB_Vec3LengthSq, @function\n"
    ".set push\n"
    ".set noreorder\n"
    ".set noat\n"
    "ColB_Vec3LengthSq:\n"
    "    .word 0xD8850000 /* lqc2 $vf5, 0x0($4) */\n"
    "    .word 0x4BC5296A /* vmul.xyz $vf5, $vf5, $vf5 */\n"
    "    .word 0x4B052941 /* vaddy.x $vf5, $vf5, $vf5y */\n"
    "    .word 0x4B052942 /* vaddz.x $vf5, $vf5, $vf5z */\n"
    "    .word 0x48222800 /* qmfc2.ni $2, $vf5 */\n"
    "    .word 0x44820000 /* mtc1 $2, $f0 */\n"
    "    .word 0x03E00008 /* jr $31 */\n"
    "    .word 0x00000000 /* nop */\n"
    ".set pop\n"
    ".size ColB_Vec3LengthSq, . - ColB_Vec3LengthSq\n"
);
#else
/* PC: the same sum in C (the word is returned in f0, the qmfc2 of vf5.x) */
f32 ColB_Vec3LengthSq(CpVec *v) {
    f32 *p = (f32 *)v;

    return (p[0] * p[0] + p[1] * p[1]) + p[2] * p[2];
}
#endif


/* Two spheres overlap or touch. */
s32 ColSphere_TestSphere(CpSphere *a, CpSphere *b) {
    CpVec d;
    f32 r = a->radius + b->radius;

    Vec4_Sub(&d, &a->pos, &b->pos);
    if (Vec3_LengthSq(&d) <= r * r) {
        return 1;
    }
    return 0;
}

/* Two spheres overlap: unit normal from b to a, a contact point and the depth. */
s32 ColSphere_ContactSphere(CpSphere *a, CpSphere *b, CpVec *nrm, CpVec *pos, f32 *depth) {
    CpVec d;
    f32 r = a->radius + b->radius;
    f32 dist;

    Vec4_Sub(&d, &a->pos, &b->pos);
    dist = Vec3_LengthSq(&d);
    if (!(dist <= r * r)) {
        return 0;
    }
    dist = sqrtf(dist);
    *depth = r - dist;
    nrm->x = d.x / dist;
    nrm->y = d.y / dist;
    nrm->z = d.z / dist;
    pos->x = a->pos.x + nrm->x * (b->radius - *depth * 0.5f);
    pos->y = a->pos.y + nrm->y * (b->radius - *depth * 0.5f);
    pos->z = a->pos.z + nrm->z * (b->radius - *depth * 0.5f);
    Vec3_Normalize(nrm, nrm);
    return 1;
}

/* Two spheres moving by moveA / moveB during the frame: the fraction of the frame at which they first touch.
   Returns 1 with *t = 0 when they overlap at the start (strictly: centres closer than the radii). Returns 0 when
   the squared relative movement is below 1.1754944e-36, when they are not approaching (relative movement .
   offset >= 0) or when the paths never touch. *t is not limited to 0..1: the caller tests it. */
s32 ColSphere_SweepSphere(CpSphere *a, CpSphere *b, CpVec *moveA, CpVec *moveB, f32 *t) {
    CpVec d;
    CpVec v;
    f32 r;
    f32 qa;
    f32 qb;
    f32 qc;
    f32 disc;

    Vec4_Sub(&d, &b->pos, &a->pos);
    Vec4_Sub(&v, moveB, moveA);
    r = b->radius + a->radius;
    qc = Vec3_Dot(&d, &d) - r * r;
    if (qc < 0.0f) {
        *t = 0.0f;
        return 1;
    }
    qa = Vec3_Dot(&v, &v);
    if (qa < 1.1754944e-36f) {
        return 0;
    }
    qb = Vec3_Dot(&v, &d);
    if (qb >= 0.0f) {
        return 0;
    }
    disc = qb * qb - qa * qc;
    if (disc < 0.0f) {
        return 0;
    }
    *t = (-qb - sqrtf(disc)) / qa;
    return 1;
}

/* Two spheres that touch (or are no more than 0.001 apart): the unit direction a -> b ((1, 0, 0) when the centres
   coincide) and each centre moved half the overlap plus 0.001 away from the other (x, y, z only). */
s32 ColSphere_SeparateSphere(CpSphere *a, CpSphere *b, CpVec *posA, CpVec *posB, CpVec *nrm) {
    f32 dist;
    f32 r;
    f32 push;

    Vec4_Sub(nrm, &b->pos, &a->pos);
    dist = sqrtf(Vec3_Dot(nrm, nrm));
    push = dist;
    if (push != 0.0f) {
        f32 inv = 1.0f / push;

        nrm->x *= inv;
        nrm->y *= inv;
        nrm->z *= inv;
        nrm->w = 1.0f;
    } else {
        nrm->x = 1.0f;
        nrm->y = 0.0f;
        nrm->z = 0.0f;
        nrm->w = 1.0f;
    }
    r = a->radius + b->radius;
    if (dist > r) {
        if (__builtin_fabsf(dist - r) > D_00387190) {
            return 0;
        }
    }
    push = (r - dist) * 0.5f + D_00387194;
    posA->x = a->pos.x - nrm->x * push;
    posA->y = a->pos.y - nrm->y * push;
    posA->z = a->pos.z - nrm->z * push;
    posB->x = b->pos.x + nrm->x * push;
    posB->y = b->pos.y + nrm->y * push;
    posB->z = b->pos.z + nrm->z * push;
    return 1;
}
