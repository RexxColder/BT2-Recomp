#include "common.h"

void func_0014EAE8(s32 arg0, s32 arg1);
u8 *func_001F3758(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);

void func_00159070(u8 *arg0, u8 *arg1) {
    s32 temp_s1;
    u8 *temp_s0;

    temp_s1 = *(s32 *)(func_001F3758((s32)arg0, (s32)arg1) + 0x38);
    temp_s0 = *(u8 **)(arg0 + 0x38);
    memset(temp_s0, 0, 0xAC0);
    *(u8 **)(temp_s0 + 8) = arg1;
    *(f32 *)(temp_s0 + 0x18) = *(f32 *)(*(u8 **)(arg1 + 0x24) + 8);
    *(f32 *)(temp_s0 + 0x1C) = *(f32 *)(*(u8 **)(arg1 + 0x24) + 4);
    func_0014EAE8(temp_s1, (s32)(temp_s0 + 0xB0));
    *(s32 *)(temp_s0 + 4) = 0;
    *(f32 *)(temp_s0 + 0xAB4) = 1.0f;
    *(s32 *)(temp_s0 + 0xAB0) = *(s16 *)(*(u8 **)(*(u8 **)(temp_s0 + 8) + 0x20) + 0x34);
    *(s32 *)(temp_s0 + 0xABC) = 0;
    *(s32 *)(temp_s0 + 0xAB8) = 0;
}
