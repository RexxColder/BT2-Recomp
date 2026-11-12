#include "common.h"

s32 func_00126040(s32 arg0);
s32 func_00210DD8(s32 arg0);
u8 *func_00211288(s32 arg0);

void func_001251B0(s32 arg0) {
    u8 *s0;
    u8 *v;
    s32 d;

    s0 = (u8 *)(arg0 + 0x10A0);
    v = func_00211288(func_00210DD8(func_00126040(arg0)));
    if (*(s32 *)(v + 0x149C) == 0) {
        *(s32 *)(s0 + 0xB4) = 0;
    } else {
        *(f32 *)(s0 + 0xB4) = (f32)*(s32 *)(v + 0x14A0) / (f32)*(s32 *)(v + 0x149C);
    }
    d = *(s32 *)(v + 0x14A4) + *(s32 *)(v + 0x14A8);
    if (d == 0) {
        *(s32 *)(s0 + 0xB8) = 0;
        return;
    }
    *(f32 *)(s0 + 0xB8) = (f32)*(s32 *)(v + 0x14A8) / (f32)d;
}
