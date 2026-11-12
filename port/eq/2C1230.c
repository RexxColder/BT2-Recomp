#include "common.h"

void func_002C32B0(s32 arg0, s32);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C1230(u8 *arg0, s32 arg1) {
    s32 sp[4];
    u8 *s0;
    s32 a2;
    s32 v1;
    s32 a3;
    s32 neg;

    s0 = arg0 + 0xD30;
    func_002C32B0((s32)sp, arg1);
    a2 = *(s32 *)(s0 + 0x164) + arg1;
    v1 = *(s32 *)(s0 + 0x168) + 1;
    *(s32 *)(s0 + 0x164) = a2;
    a3 = v1 + 0x1F;
    neg = v1 < 0;
    *(s32 *)(arg0 + (((v1 - ((((neg != 0) ? a3 : v1) >> 5) << 5)) * 4)) + 0xE9C) = a2;
    *(s32 *)(s0 + 0x168) = v1;
    func_002C32C8((s32)sp, neg, a2, a3);
}
