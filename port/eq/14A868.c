#include "common.h"

u8 *func_001F3758(s32 arg0, s32 arg1);
void func_0014EAE8(s32 arg0, s32 arg1);
void *memset(void *s, s32 c, u32 n);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_0012D3A0(s32 arg0, s32 arg1, s32 arg2);

void func_0014A868(u8 *arg0, s32 arg1) {
    s32 sp[4];
    s32 temp_s1;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    temp_s1 = *(s32 *)(func_001F3758((s32)arg0, arg1) + 0x38);
    memset(temp_s0, 0, 0xAB0);
    *(s32 *)(temp_s0 + 0xB0) = arg1;
    temp_v0 = *(u8 **)(arg1 + 0x24);
    *(f32 *)(temp_s0 + 0x10) = *(f32 *)(temp_v0 + 8);
    *(f32 *)(temp_s0 + 0x14) = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s0 + 0x18) = *(f32 *)(temp_v0 + 4);
    func_0014EAE8(temp_s1, (s32)(temp_s0 + 0xB4));
    func_00208DE8(*(s32 *)*(u8 **)(temp_s0 + 0xB0), (s32)sp, 0x11);
    func_0012D3A0((s32)(temp_s0 + 0x30), (s32)sp, *(s32 *)*(u8 **)(temp_s0 + 0xB0));
}
