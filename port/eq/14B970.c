#include "common.h"

s32 func_001F3758(s32 arg0, s32 arg1);
void func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0014B970(s32 arg0, s32 arg1) {
    s32 ret;
    s32 s0;
    s32 s1;
    s32 t;

    ret = func_001F3758(arg0, arg1);
    s0 = *(s32 *)(arg0 + 0x38);
    s1 = *(s32 *)(ret + 0x38);
    memset((void *)s0, 0, 0xCC0);
    *(s32 *)(s0 + 0xB0) = arg1;
    t = *(s32 *)(arg1 + 0x24);
    *(f32 *)(s0 + 0x14) = *(f32 *)(t + 8);
    *(f32 *)(s0 + 0x18) = *(f32 *)(t + 4);
    *(f32 *)(s0 + 0x1C) = *(f32 *)(t + 4);
    func_0014EAE8(s1, s0 + 0xB4);
}
