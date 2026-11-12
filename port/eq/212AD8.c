#include "common.h"

extern u8 *D_003876A0;
extern f32 D_00385A48;

f32 sinf(f32 arg0);
void func_0028C810(s32 arg0, s32 arg1, s32 arg2);

#define W(p, off) (*(s32 *)((p) + (off)))
#define F(p, off) (*(f32 *)((p) + (off)))

void func_00212AD8(u8 *arg0) {
    u8 *s0;
    u8 *q;
    s32 s1;
    s32 s2;
    s32 a1;
    s32 v0;
    s32 v1;
    f32 f0;
    f32 f1;
    f32 f12;
    f32 f20;

    s0 = arg0 + 0x13C;
    s2 = W(arg0, 0x153C);
    if (*(s64 *)(D_003876A0 + 0x4D8) & ((s64)1 << 34)) {
        return;
    }
    q = D_003876A0 + 0x1D0 * W(arg0, 0x1534);
    if (*(u8 *)(q + 0x2A4) != 0) {
        W(s0, 0x8) = 0;
        W(s0, 0x4) = 0;
        return;
    }

    a1 = 0;
    s1 = 0;
    if (W(s0, 0x4) > 0) {
        f12 = ((f32)W(s0, 0xC) * D_00385A48) / 30.0f;
        f20 = 0.5f;
        f0 = sinf(f12);
        f1 = F(s0, 0x0);
        f0 = f0 * f20;
        f1 = f1 * 127.0f;
        W(s0, 0xC) = W(s0, 0xC) + 1;
        f0 = f0 + f20;
        f0 = f0 * f20;
        f0 = f0 + f20;
        f1 = f1 * f0;
        a1 = (s32)f1;
        v0 = W(s0, 0x8);
    } else {
        W(s0, 0xC) = 0;
        v0 = W(s0, 0x8);
    }

    if (v0 > 0) {
        v0 = W(s0, 0x10);
        W(s0, 0x10) = v0 + 1;
        s1 = ((v0 & 1) == 0);
    } else {
        W(s0, 0x10) = 0;
    }

    func_0028C810(s2, a1, s1);

    v0 = W(s0, 0x4) - 1;
    v1 = W(s0, 0x8) - 1;
    if (v0 < 0) {
        v0 = 0;
    }
    if (v1 < 0) {
        v1 = 0;
    }
    W(s0, 0x4) = v0;
    W(s0, 0x8) = v1;
}
