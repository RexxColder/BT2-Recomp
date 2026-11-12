#include "common.h"

s32 func_001F3758(s32 arg0);
void func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);
extern f32 D_00384914;

void func_00176068(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    f32 temp_f0;

    temp_v0 = func_001F3758(arg0);
    temp_s0 = *(s32 *)(arg0 + 0x38);
    temp_s1 = *(s32 *)(temp_v0 + 0x38);
    memset((void *)temp_s0, 0, 0xAE0);
    *(s32 *)(temp_s0 + 0xC0) = arg1;
    *(f32 *)(temp_s0 + 0x14) = D_00384914;
    temp_v0 = *(s32 *)(arg1 + 0x24);
    temp_f0 = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s0 + 0x18) = temp_f0;
    *(f32 *)(temp_s0 + 0x20) = temp_f0;
    *(f32 *)(temp_s0 + 0x1C) = *(f32 *)(temp_v0 + 4);
    func_0014EAE8(temp_s1, temp_s0 + 0xC4);
}
