#include "common.h"

u8 *func_001F3758(s32 arg0, s32 arg1);
s32 func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001559B8(u8 *arg0, u8 *arg1) {
    u8 *temp_s0;
    s32 temp_s1;
    u8 *temp_v0;
    u8 *p;

    p = func_001F3758((s32)arg0, (s32)arg1);
    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s1 = *(s32 *)(p + 0x38);
    memset(temp_s0, 0, 0xAC0);
    *(u8 **)(temp_s0 + 0xA0) = arg1;
    temp_v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(temp_s0 + 0x10) = *(f32 *)(temp_v0 + 0x8);
    *(f32 *)(temp_s0 + 0x14) = *(f32 *)(temp_v0 + 0x4);
    func_0014EAE8(temp_s1, (s32)(temp_s0 + 0xA4));
}
