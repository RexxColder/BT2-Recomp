#include "common.h"

/*
 * Integer vector helpers, 0x11FA10..0x11FE80: the head of the vector / matrix library (config/symbols/vu0_a.txt).
 * A vector is four s32. The IVec3 forms leave the fourth word of the destination untouched, except IVec3_Clamp.
 * IVec4_Swap, IVec4_Copy and the three VU0 conversions are hand-written assembly in the original and are kept as
 * top-level assembly here (same bytes, checked by fdiff). Portable reference versions of the whole library half
 * are in src/port/vu0_a.c (bt3-port repository).
 */

typedef struct IVec4 {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s32 w;
} IVec4; /* size 0x10 */

/* v = (0, 0, 0, 1). */
void IVec4_SetZeroW1(IVec4 *v);

/* v = (0, 0, 0, 0). */
void IVec4_SetZero(IVec4 *v) {
    v->x = 0;
    v->y = 0;
    v->z = 0;
    v->w = 0;
}

/* v = (x, y, z, w). */
void IVec4_Set(IVec4 *v, s32 x, s32 y, s32 z, s32 w);

/* v = (x, y, z), w untouched. */
void IVec3_Set(IVec4 *v, s32 x, s32 y, s32 z);

/* void IVec4_Swap(IVec4 *a, IVec4 *b): swaps two vectors with 128-bit moves. Hand-written assembly ($t0 / $t1); the
 * compiler's own 128-bit moves use $v0 / $v1:
 *     IVecQword t0 = *(IVecQword *)a, t1 = *(IVecQword *)b; *(IVecQword *)b = t0; *(IVecQword *)a = t1; */


/* out = a + b on four components. */
void IVec4_Add(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a + b on x, y, z. */
void IVec3_Add(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a - b on four components. */
void IVec4_Sub(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a - b on x, y, z. */
void IVec3_Sub(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a * b per component (low 32 bits), four components. */
void IVec4_Mul(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a * b per component on x, y, z. */
void IVec3_Mul(IVec4 *out, IVec4 *a, IVec4 *b);

/* out = a * s on four components. */
void IVec4_Scale(IVec4 *out, IVec4 *a, s32 s);

/* out = a * s on x, y, z. */
void IVec3_Scale(IVec4 *out, IVec4 *a, s32 s);

/* out = a / s (signed, truncating) on four components. */
void IVec4_Div(IVec4 *out, IVec4 *a, s32 s);

/* out = a / s (signed, truncating) on x, y, z. */
void IVec3_Div(IVec4 *out, IVec4 *a, s32 s);

/* void IVec4_Copy(IVec4 *out, IVec4 *in): out = in, one 128-bit move. Hand-written assembly ($t0). */


/* out = in on x, y, z. */
void IVec3_Copy(IVec4 *out, IVec4 *in);

/* void IVec4_ToFloat12(f32 *out, IVec4 *in): out = (f32)in / 4096 on four components (VU0 vitof12). */


/* void IVec4_ToFloat4(f32 *out, IVec4 *in): out = (f32)in / 16 on four components (VU0 vitof4). */


/* void IVec4_ToFloat(f32 *out, IVec4 *in): out = (f32)in on four components (VU0 vitof0). */


/* out = in clamped to [lo, hi] (signed) on four components; lo wins when in < lo. */
void IVec4_Clamp(IVec4 *out, IVec4 *in, s32 lo, s32 hi);

/* out = in clamped to [lo, hi] (signed) on x, y, z; out.w = in.w. */
void IVec3_Clamp(IVec4 *out, IVec4 *in, s32 lo, s32 hi);

/* Empty; no callers. */
void IVec_Stub(void);
