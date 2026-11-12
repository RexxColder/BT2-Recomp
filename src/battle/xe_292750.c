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

/* Two 2D lines p + t (q - p) and r + u (s - r): writes t of their crossing; 0 when they are parallel. */
s32 ColLine2_Intersect(f32 *p, f32 *q, f32 *r, f32 *s, f32 *t) {
    CpVec d1;
    CpVec d2;
    f32 det;

    d1.x = q[0] - p[0];
    d1.y = q[1] - p[1];
    d2.x = r[0] - s[0];
    d2.y = r[1] - s[1];
    det = d2.y * d1.x - d2.x * d1.y;
    if (det == 0.0f) {
        return 0;
    }
    if (t != NULL) {
        *t = (d2.x * (p[1] - r[1]) - d2.y * (p[0] - r[0])) / det;
    }
    return 1;
}
