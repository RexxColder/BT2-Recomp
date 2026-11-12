#include "m2c_macros.h"

s32 func_00211310(void *obj, s32 a1, s32 a2);
void BtlOpp_GetTargetPos(void *obj, f32 *out);
void func_00210970(void *obj, f32 *out);
f32 func_0029DFD0(f32 *v);
void func_00210868(void *obj, f32 *out);
f32 sinf(f32 x);
f32 cosf(f32 x);
f32 sqrtf(f32 x);
void func_00312680(f32 *dst, f32 *a, f32 ang);
void func_00312638(f32 *dst, f32 *a, f32 *b);
void func_003126C8(f32 *dst, f32 *a);
f32 func_002086B0(s32 id);
f32 func_00210D10(void *obj);
void *BtlChar_GetPos(void *obj);
extern f32 D_00385AA8;
extern f32 D_00385AAC;

void func_002163B8(void *obj, f32 ang) {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 d[4];
    f32 s;
    f32 r10;
    f32 r11;
    f32 sum;
    f32 r;
    f32 *p;

    if (func_00211310(obj, 0, 1) == 0) {
        return;
    }
    BtlOpp_GetTargetPos(obj, a);
    func_00210970(obj, b);
    if (func_0029DFD0(b) < D_00385AA8) {
        func_00210868(obj, d);
        s = D_00385AA8;
        b[0] = -sinf(d[1]) * s;
        b[1] = 0.0f;
        b[2] = -cosf(d[1]) * s;
        b[3] = 0.0f;
    }
    func_00312680(c, b, ang);
    func_00312638(a, a, c);
    s = 0.0f;
    func_003126C8(c, b);
    r10 = func_002086B0(M2C_FIELD(obj, s32 *, 0x1534));
    s = r10 + s;
    r11 = func_00210D10(obj);
    sum = c[0] * c[0] + c[2] * c[2];
    s = s + r11;
    r = sqrtf(r11);
    if (r != r) {
        r = sqrtf(sum);
    }
    if (D_00385AAC < r) {
        f32 k = s / r;
        c[0] = c[0] * k;
        c[2] = c[2] * k;
    }
    p = BtlChar_GetPos(obj);
    func_00312638(p, a, c);
}
