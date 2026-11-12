#include "common.h"

s32 Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0014EAE8(s32 arg0, s32 arg1);
/* GUESS arity: a0/a1 are not written before this call, passed through */
u8 *func_001F3758(s32 arg0, s32 arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_003848F0;

void func_00173690(u8 *arg0, s32 arg1) {
    s32 temp_s1;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = (u8 *)*(s32 *)(arg0 + 0x38);
    temp_s1 = *(s32 *)(func_001F3758((s32)arg0, arg1) + 0x38);
    memset(temp_s0, 0, 0xAB0);
    *(s32 *)(temp_s0 + 0xB0) = arg1;
    temp_v0 = (u8 *)*(s32 *)(arg1 + 0x24);
    *(f32 *)(temp_s0 + 0x10) = *(f32 *)(temp_v0 + 8);
    *(f32 *)(temp_s0 + 0x14) = *(f32 *)(temp_v0 + 4);
    *(f32 *)(temp_s0 + 0x10) = D_003848F0;
    *(f32 *)(temp_s0 + 0x18) = *(f32 *)(temp_v0 + 4);
    Vec4_Set((s32)(temp_s0 + 0x30), 0.0f, 0.0f, 1.0f, 1.0f);
    func_0014EAE8(temp_s1, (s32)(temp_s0 + 0xB4));
}
