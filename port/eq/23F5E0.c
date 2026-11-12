#include "common.h"

s32 BtlParam_GetType(void *a0);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_00203C58(void *a0, s64 a1);
void *memcpy(void *arg0, const void *arg1, u32 arg2);
extern u8 D_00371FC8 __attribute__((section(".data")));

f32 func_0023F5E0(void *arg0) {
    u8 buf[0x28];
    f32 f20;
    s32 t;
    s32 v0;

    memcpy(buf, &D_00371FC8, 0x28);
    t = BtlParam_GetType(arg0);
    f20 = *(f32 *)(buf + 4 * t);
    v0 = func_00211310(arg0, 0, 0x10000);
    if (v0 != 0) {
        f20 = *(f32 *)(buf + 0x1C);
    }
    if (func_00203C58(arg0, 4) != 0) {
        f20 = f20 + f20;
    }
    return f20;
}
