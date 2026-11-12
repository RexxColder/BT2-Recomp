#include "common.h"

#define GP(a) ((u8 *)BtlChar_GetPos(a))

void *BtlChar_GetPos(s32 arg0);
void func_00218128(s32 arg0, s32 arg1);
f32 func_0029DFD0(s32 arg0);
void func_00312680(s32 arg0, s32 arg1, f32 farg0);
extern f32 D_00385AA4;

void func_00216208(f32 farg0, f32 farg1, s32 arg0) {
    f32 f21;
    f32 f20;
    f32 f0;
    u8 *b;
    u8 *c;
    u8 *d;
    u8 *e;
    u8 *i;
    u8 *j;
    u8 *k;
    u8 *l;
    u8 *m;
    u8 *n;
    u8 *o;
    u8 *p;
    u8 *q;
    u8 *r;

    f21 = farg0;
    f20 = farg1;
    func_00218128(arg0, 2);
    f0 = *(f32 *)(GP(arg0) + 0xC0) + f20;
    if (f0 < f21) {
        b = GP(arg0);
        *(f32 *)(b + 0xC0) = *(f32 *)(b + 0xC0) + f20;
    } else {
        c = GP(arg0);
        f0 = *(f32 *)(c + 0xC0) - f20;
        if (f21 < f0) {
            d = GP(arg0);
            *(f32 *)(d + 0xC0) = *(f32 *)(d + 0xC0) - f20;
        } else {
            e = GP(arg0);
            *(f32 *)(e + 0xC0) = f21;
        }
    }

    f20 = func_0029DFD0((s32)GP(arg0) + 0x30);
    if (D_00385AA4 < f20) {
        i = GP(arg0);
        j = GP(arg0);
        func_00312680((s32)i + 0x30, (s32)j + 0x30, 1.0f / f20);
    }

    k = GP(arg0);
    f20 = *(f32 *)(k + 0xC0);
    l = GP(arg0);
    m = GP(arg0);
    *(f32 *)l = *(f32 *)l + *(f32 *)(m + 0x30) * f20;
    n = GP(arg0);
    o = GP(arg0);
    *(f32 *)(n + 4) = *(f32 *)(n + 4) + *(f32 *)(o + 0x34) * f20;
    p = GP(arg0);
    q = GP(arg0);
    *(f32 *)(p + 8) = *(f32 *)(p + 8) + *(f32 *)(q + 0x38) * f20;
    r = GP(arg0);
    *(f32 *)(r + 0xC) = 1.0f;
}
