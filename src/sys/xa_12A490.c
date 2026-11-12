#include "common.h"
/* BT2 targets of these calls / globals (checked against the original relocations). */
#define Mathf_Sin func_0012A3F8

/* Float constants: the original .lit4 words (bits checked against the data). */
extern const f32 D_00384164; /* MATHF_HALF_PI */
#include "sys/mathf.h"

/*
 * Scalar float maths helpers, 0x11F548..0x11F7D8.
 *
 * Two families of sine / cosine exist and they do not return the same bits:
 *   Mathf_Sin / Mathf_Cos          wrap the angle, then call libm sinf (cos is sin(angle + pi/2)).
 *   Mathf_SinFast / Mathf_CosFast  wrap the angle, then evaluate a degree-9 odd polynomial on VU0.
 * The wrap (Mathf_WrapAngle) is done by repeated float addition / subtraction of 2*pi, not by fmod, so the result
 * carries one rounding per turn removed, and an angle so large that adding 2*pi does not change it never ends.
 *
 * Mathf_WrapAngle, Mathf_SinFast and Mathf_Sqrt are assembly (VU0 or hand-written) and stay INCLUDE_ASM; an
 * equivalent that assembles to the same bytes is kept above each one.
 */

extern f32 sinf(f32 x);
extern f32 tanf(f32 x);
extern f32 asinf(f32 x);
extern f32 acosf(f32 x);
extern f32 atanf(f32 x);

/* Polynomial coefficients of Mathf_SinFast, highest power first: x^9, x^7, x^5, x^3. */
extern f32 gMathfSinCoef[4];

/*
 * Brings an angle into (-half, half] in steps of 2 * half. Hand-written assembly: the first two instructions are
 * dead (f0 = 0, f0 = -half) and the lower bound actually tested is +2 * half, so what runs is
 *
 *     f32 range = half + half;
 *     while (angle < range) angle += range;
 *     while (half < angle) angle -= range;
 *     return angle;
 *
 * i.e. every angle is first pushed up to at least 2 * half and then brought back down.
 */


/* sinf of the angle wrapped to (-pi, pi]. */
f32 Mathf_Sin(f32 angle);

/*
 * Polynomial sine on VU0 of the angle wrapped to (-pi, pi]:
 *     x + c[3] x^3 + c[2] x^5 + c[1] x^7 + c[0] x^9
 * with x^3 formed as (c * x) * x^2 and each further power by one more multiply by x^2; the four terms are added to
 * x in the order x^3, x^5, x^7, x^9. VU0 inline assembly.
 */
f32 Mathf_SinFast(f32 angle);

/* Cosine through libm: Mathf_Sin(angle + pi/2). */
f32 Mathf_Cos(f32 angle) {
    return Mathf_Sin(angle + D_00384164);
}

/* Cosine through the polynomial: Mathf_SinFast(angle + pi/2). */
f32 Mathf_CosFast(f32 angle);

/* tanf of the angle wrapped to [-pi, pi] in steps of 2*pi. */
f32 Mathf_Tan(f32 angle);

/* Square root on VU0 (vsqrt, result read from the Q register). VU0 assembly. */
f32 Mathf_Sqrt(f32 x);

/* out[0] = Mathf_Sin(angle), out[1] = Mathf_Cos(angle). */
void Mathf_SinCos(f32 *out, f32 angle);

/* asinf with the argument clamped to [-1, 1]. */
f32 Mathf_Asin(f32 x);

/* acosf with the argument clamped to [-1, 1]. */
f32 Mathf_Acos(f32 x);

/* atanf. */
f32 Mathf_Atan(f32 x);
