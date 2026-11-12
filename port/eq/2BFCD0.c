#include "common.h"

void func_002BFE48(s32 arg0, s32 arg1, s32 arg2);

void func_002BFCD0(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 *s1;
    u8 *s2;
    u8 *s0;

    s1 = arg1 + arg3 * 4;
    s2 = arg2 + arg3 * 4;
    s0 = arg0 + arg3 * 0x74;
    func_002BFE48((s32)s0, 2, (*(u32 *)s2 != 0));
    s0 += 0x10;
    *(s32 *)(s0 + 0) = *(s32 *)s1;
    *(s32 *)(s0 + 4) = *(s32 *)s2;
    *(s32 *)(s0 + 0x2C) = 0;
    *(s32 *)(s0 + 8) = 0;
    *(s32 *)(s0 + 0xC) = 0;
    *(s32 *)(s0 + 0x10) = 0;
    *(s32 *)(s0 + 0x14) = 0;
    *(s32 *)(s0 + 0x18) = 0;
    *(s32 *)(s0 + 0x1C) = 0;
    *(s32 *)(s0 + 0x20) = 0;
    *(s32 *)(s0 + 0x24) = 0;
    *(s32 *)(s0 + 0x28) = 0;
}
