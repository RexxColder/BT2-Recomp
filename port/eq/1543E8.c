#include "common.h"

void func_0014EAE8(s32 arg0, s32 arg1);
u8 *func_001F3758(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001543E8(u8 *arg0, u8 *arg1) {
    s32 temp_s1;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = (u8 *)*(s32 *)(arg0 + 0x38);
    temp_s1 = *(s32 *)(func_001F3758((s32)arg0, (s32)arg1) + 0x38);
    memset(temp_s0, 0, 0xB00);
    *(s32 *)(temp_s0 + 0xC0) = (s32)arg1;
    temp_v0 = (u8 *)*(s32 *)(arg1 + 0x24);
    *(f32 *)(temp_s0 + 0x14) = *(f32 *)(temp_v0 + 8);
    *(f32 *)(temp_s0 + 0x20) = 15.0f;
    *(f32 *)(temp_s0 + 0x18) = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s0 + 0x24) = -10.0f;
    *(f32 *)(temp_s0 + 0x28) = -1.0f;
    *(f32 *)(temp_s0 + 0x1C) = 15.0f;
    func_0014EAE8(temp_s1, (s32)(temp_s0 + 0xC4));
}
