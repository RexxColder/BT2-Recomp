#include "common.h"

void func_002C32B0(s32 arg0, s32, s32);
void func_002C32C8(s32 arg0);

s32 func_002C1370(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 sp[4];
    u8 *s0;
    s32 v1;
    s32 result;

    s0 = (u8 *)arg0 + 0xD30;
    func_002C32B0((s32)sp, arg1, arg2);
    if (*(s32 *)(s0 + 0x1F4) - *(s32 *)(s0 + 0x1F8) <= 0) {
        result = 0;
        *arg1 = -1;
    } else {
        result = 1;
        *arg2 = *(s32 *)(s0 + 0x1EC);
        v1 = *(s32 *)(s0 + 0x1F8);
        *arg1 = *(s32 *)((u8 *)arg0 + (v1 - (((v1 < 0 ? v1 + 0x1F : v1) >> 5) << 5)) * 4 + 0xF2C);
        *(s32 *)(s0 + 0x1F8) = *(s32 *)(s0 + 0x1F8) + 1;
    }
    func_002C32C8((s32)sp);
    return result;
}
