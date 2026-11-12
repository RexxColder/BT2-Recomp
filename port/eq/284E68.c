#include "common.h"

extern u8 D_00376EA0[] __attribute__((section(".data")));
extern u8 D_00388F30[] __attribute__((section(".data")));
s32 func_003126C8(s32 arg0, s32 arg1);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);

void func_00284E68(s32 arg0, s32 arg1, f32 farg0) {
    u8 buf[0x60];
    u32 idx;
    s32 s3;
    u8 *s2;
    u8 *s1;
    u8 *s0;
    s32 k;

    for (k = 0; k < 0x60; k++) {
        buf[k] = D_00376EA0[k];
    }
    idx = ((u32)arg0 < 3U) ? (u32)arg0 : 0;
    s3 = idx * 2;
    s2 = D_00388F30 + idx * 0x60;
    *(s8 *)(s2 + 0x58) = (arg1 != 0) ? 2 : 4;
    s1 = s2 + 0x10;
    s0 = s2 + 0x20;
    func_003126C8((s32)s1, (s32)(buf + (s3 + arg1) * 0x10));
    func_003126C8((s32)s0, (s32)(buf + (s3 + (arg1 ^ 1)) * 0x10));
    func_00312650((s32)(s2 + 0x30), (s32)s0, (s32)s1);
    Ramp_Start((s32)(s2 + 0x40), farg0, 0.0f, 1.0f);
}
