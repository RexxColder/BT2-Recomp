#include "common.h"

void func_00312650(u8 *out, u8 *a, u8 *b);
f32 sceVu0InnerProduct(u8 *a, u8 *b);

/* 0x00268BC8 ObjShadow_CalcScreenDist(a, b, r, scale): len = |v|, d = (r/len)^2, result = len*sqrt(1-d)*scale/(2r) */
f32 ObjShadow_CalcScreenDist(u8 *a, u8 *b, f32 r, f32 scale) {
    u8 sp[16];
    f32 len;
    f32 d;

    func_00312650(sp, a, b);
    len = __builtin_sqrtf(sceVu0InnerProduct(sp, sp));
    d = r / len;
    d = d * d;
    return (len * __builtin_sqrtf(1.0f - d)) * scale / (r + r);
}
