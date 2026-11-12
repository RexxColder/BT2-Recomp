#include "common.h"

void func_002C32B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346DE0 __attribute__((section(".data")));

void func_002D2030(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[4];
    s32 temp_s1;
    u8 *temp_s0;

    temp_s0 = (u8 *)arg0 + 0xD30;
    temp_s1 = func_002E0A98(D_00346DE0, arg1, arg2);
    func_002C32B0((s32)sp, arg1, arg2, arg3);
    *(s32 *)(temp_s0 + 0x2A8) = *(s32 *)(temp_s0 + 0x2A8) + temp_s1;
    *(s32 *)(temp_s0 + 0x2CC) = *(s32 *)(temp_s0 + 0x2CC) + temp_s1;
    func_002C32C8((s32)sp, arg1, arg2, arg3);
}
