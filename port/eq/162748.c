#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);

void func_00162748(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    f32 temp_f1;

    temp_v0 = func_001F3758(arg0);
    temp_s0 = *(s32 *)(arg0 + 0x38);
    temp_s1 = *(s32 *)(temp_v0 + 0x38);
    memset((void *)temp_s0, 0, 0xAC0);
    *(s32 *)(temp_s0 + 0xB0) = arg1;
    temp_v0 = *(s32 *)(arg1 + 0x24);
    *(f32 *)(temp_s0 + 0x10) = *(f32 *)(temp_v0 + 8);
    temp_f1 = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s0 + 0x14) = temp_f1;
    *(f32 *)(temp_s0 + 0x1C) = temp_f1;
    *(f32 *)(temp_s0 + 0x18) = *(f32 *)(temp_v0 + 4);
    func_0014EAE8(temp_s1, temp_s0 + 0xB4);
}
