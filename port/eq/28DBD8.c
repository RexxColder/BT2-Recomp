#include "common.h"

extern f32 D_003870FC;
extern f32 D_00387100;
f32 Vec3_LengthSq(u8 *v);
s32 Col_NearEq(f32 a, f32 b, f32 eps);
void func_00312650(u8 *out, u8 *a, u8 *b);
f32 sceVu0InnerProduct(u8 *a, u8 *b);

/* 0x0028DBD8 Col_LineLineParams: closest-point parameters (*s, *t) of two lines (pointC,dirA) and (pointD,dirB).
 * Both are 0 when either direction is not unit length or the lines are parallel. */
void Col_LineLineParams(f32 *s, f32 *t, u8 *pointC, u8 *dirA, u8 *pointD, u8 *dirB) {
    u8 w[16];
    f32 wa;
    f32 wb;
    f32 ab;
    f32 den;
    f32 inv;
    f32 eps = D_003870FC;

    if (Col_NearEq(Vec3_LengthSq(dirA), 1.0f, eps) != 0 ||
        Col_NearEq(Vec3_LengthSq(dirB), 1.0f, eps) != 0) {
        *s = 0.0f;
        *t = 0.0f;
        return;
    }
    func_00312650(w, pointD, pointC);
    wa = sceVu0InnerProduct(w, dirA);
    wb = sceVu0InnerProduct(w, dirB);
    ab = sceVu0InnerProduct(dirA, dirB);
    den = ab * ab - 1.0f;
    if (den < D_00387100) {
        inv = 1.0f / den;
        *s = (ab * wb - wa) * inv;
        *t = (wb - ab * wa) * inv;
    } else {
        *s = 0.0f;
        *t = 0.0f;
    }
}
