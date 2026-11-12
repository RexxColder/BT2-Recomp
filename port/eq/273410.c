#include "common.h"

s32 func_002732B0(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
s32 func_00273388(s32 arg0, s32 arg1);
void func_00273410(s32 arg0, s32 arg1, f32 farg0);
extern u8 *gBtlCamView;
extern u8 *gBtlStage;

void func_00273410(s32 arg0, s32 arg1, f32 farg0) {
    u8 *self;
    u8 *node;
    u8 *base;
    u8 *s6;
    u8 *s7;
    u8 *list;
    u8 *e;
    u8 *s0;
    s32 s4;
    s32 s5;
    s32 s1;
    s32 s2;
    s32 k;
    s32 v;
    s32 cnt;
    s32 cu;
    f32 f1;
    f32 f0;
    f32 f14;

    self = (u8 *)arg0;
    s4 = arg1;
    s5 = (s32)(gBtlCamView + 0x180);
    base = (u8 *)*(s32 *)(gBtlStage + 0x5C);
    s6 = base + *(s32 *)(gBtlStage + 0x2C) * 4;
    f1 = farg0 + farg0;
    f0 = (f32)(2 << (*(s32 *)(self + 0x20) & 31));
    f14 = f1 / f0;
    if (s4 == 1) {
        s4 = func_002732B0(s5, *(f32 *)(self + 0x18), *(f32 *)(self + 0x1C), f14);
        if (s4 == 2) {
            *(s32 *)(self + 0x14) = s4;
            return;
        }
    }
    *(s32 *)(self + 0x14) = 0;

    s2 = 0;
    s7 = base + *(s32 *)(self + 0x28) * 4;
    cnt = *(s32 *)(self + 0x24);
    if (cnt > 0) {
        do {
            node = base + *(s32 *)(s7 + s2 * 4) * 4;
            if ((*(u16 *)(node + 2) & 1) != 0) {
                if (func_00273388((s32)node, s5) != 2) {
                    cu = *(u16 *)node;
                    if (cu != 0) {
                        list = base + *(s32 *)(node + 4) * 4;
                        k = 0;
                        do {
                            e = base + *(s32 *)(list + k * 4) * 4;
                            *(s6 + *(u16 *)e) = 1;
                            k += 1;
                        } while (k < cu);
                    }
                }
            }
            s2 += 1;
        } while (s2 < *(s32 *)(self + 0x24));
    }

    for (s1 = 0; s1 < 2; s1++) {
        s0 = self + 4 + s1 * 8;
        s2 = 1;
        v = *(s32 *)s0;
        do {
            s0 += 4;
            if (v != 0) {
                func_00273410((s32)(base + v * 4), s4, farg0);
            }
            s2 -= 1;
            if (s2 >= 0) {
                v = *(s32 *)s0;
            }
        } while (s2 >= 0);
    }
}
