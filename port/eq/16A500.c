#include "common.h"

s32 rand(void);
extern f32 D_0038484C;
extern f32 D_00384850;
extern f32 D_00384854;

void func_0016A500(s32 arg0_unused, u8 *arg1) {
    f32 r;
    f32 m;

    r = (f32)rand();
    m = *(f32 *)(arg1 + 0x60);
    r = ((r / D_0038484C) * D_00384850) + D_00384854;
    *(f32 *)(arg1 + 0x60) = m * r;

    r = (f32)rand();
    *(s32 *)(arg1 + 0x68) = 0;
    m = *(f32 *)(arg1 + 0x64);
    r = ((r / D_0038484C) * D_00384850) + D_00384854;
    *(f32 *)(arg1 + 0x64) = m * r;
}
