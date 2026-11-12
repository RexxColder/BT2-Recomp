#include "common.h"

f32 floorf(f32 farg0);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
s32 func_00312680(void *arg0, void *arg1, f32 farg0);
void func_003125D0(f32 farg0, void *arg1, void *arg2);

s32 func_001E5098(u8 *arg0, s32 arg1, s32 arg2, f32 *arg3) {
    u8 tmp[16];
    u8 *m;
    u8 *vel;
    f32 ctr;
    f32 lo;
    f32 hi;
    s32 i;

    m = arg0 + 0x60;

    *(f32 *)(m + 0x08) = (f32)arg1;
    ctr = floorf((f32)(arg1 + arg2) * 0.5f);
    *(f32 *)(m + 0x0C) = ctr;
    lo = ctr - *(f32 *)(m + 0x08);
    hi = (f32)arg2 - ctr;
    *(f32 *)(m + 0x10) = (f32)arg2;
    *(f32 *)(m + 0x00) = lo;
    *(f32 *)(m + 0x04) = hi;

    *(s32 *)(m + 0x50) = *(s32 *)(arg0 + 0x40);
    *(s32 *)(m + 0x54) = *(s32 *)(arg0 + 0x44);
    *(s32 *)(m + 0x58) = *(s32 *)(arg0 + 0x48);
    *(s32 *)(m + 0x5C) = *(s32 *)(arg0 + 0x4C);
    *(s32 *)(m + 0x60) = *(s32 *)(arg0 + 0x40);
    *(s32 *)(m + 0x64) = *(s32 *)(arg0 + 0x44);
    *(s32 *)(m + 0x68) = *(s32 *)(arg0 + 0x48);
    *(s32 *)(m + 0x6C) = *(s32 *)(arg0 + 0x4C);
    for (i = 0; i < 4; i++) {
        *(s32 *)(m + 0x80 + i * 4) = *(s32 *)((u8 *)arg3 + i * 4);
    }

    if (lo > 0.0f) {
        func_00312638(tmp, arg0 + 0xE0, arg0 + 0xC0);
        func_00312680(arg0 + 0xD0, tmp, 0.5f);
    } else {
        *(s32 *)(m + 0x70) = *(s32 *)(arg0 + 0x40);
        *(s32 *)(m + 0x74) = *(s32 *)(arg0 + 0x44);
        *(s32 *)(m + 0x78) = *(s32 *)(arg0 + 0x48);
        *(s32 *)(m + 0x7C) = *(s32 *)(arg0 + 0x4C);
    }
    vel = m + 0x70;

    func_00312650(m + 0x30, vel, m + 0x60);
    func_00312650(m + 0x40, m + 0x80, vel);

    if (*(f32 *)m < 1.0f) {
        *(f32 *)m = 1.0f;
    }
    if (*(f32 *)(m + 0x4) < 1.0f) {
        *(f32 *)(m + 0x4) = 1.0f;
    }
    func_003125D0(*(f32 *)m, m + 0x30, m + 0x30);
    func_003125D0(*(f32 *)(m + 0x4), m + 0x40, m + 0x40);
    func_00312680(m + 0x30, m + 0x30, 1.0f);
    return func_00312680(m + 0x40, m + 0x40, 1.0f);
}
