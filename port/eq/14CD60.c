#include "common.h"

u8 *func_001F3758(s32 arg0, s32 arg1);
void func_0014EAE8(s32 arg0, s32 arg1);
s32 func_0020A440(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0014CD60(u8 *arg0, s32 *arg1) {
    u8 *temp_s2;
    s32 temp_s0;
    u8 *temp_v0;

    temp_s2 = (u8 *)*(s32 *)(arg0 + 0x38);
    temp_s0 = *(s32 *)(func_001F3758((s32)arg0, (s32)arg1) + 0x38);
    memset(temp_s2, 0, 0xCC0);
    *(s32 *)(temp_s2 + 0xB0) = (s32)arg1;
    temp_v0 = (u8 *)*(s32 *)((u8 *)arg1 + 0x24);
    *(f32 *)(temp_s2 + 0x10) = *(f32 *)(temp_v0 + 8);
    *(f32 *)(temp_s2 + 0x14) = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s2 + 0x1C) = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s2 + 0x18) = *(f32 *)(temp_v0 + 4);
    func_0014EAE8(temp_s0, (s32)(temp_s2 + 0xB4));
    temp_v0 = (u8 *)*(s32 *)(temp_s2 + 0xB0);
    if (func_0020A440(*(s32 *)temp_v0) != 0) {
        *(s8 *)(temp_s2 + 0xB18) = 1;
    }
}
