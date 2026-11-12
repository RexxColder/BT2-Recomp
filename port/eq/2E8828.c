#include "common.h"

s32 func_002E8708(s32 arg0, s32 arg1, s16 *arg2, u8 *arg3, u8 *t0, u8 *t1, u8 *t2, u8 *t3, u8 *sp0, u8 *sp8, u8 *sp10);

s32  func_002E8828(u8 *arg0, s32 arg1, s32 arg2) {
    s16 sp20;

    *(s16 *)(arg0 + 2) = 1;
    if (func_002E8708(arg1, arg2, &sp20, arg0 + 0xC, arg0 + 0xD, arg0 + 0xF, arg0 + 0xE, arg0 + 0x14,
                      arg0 + 0x18, arg0 + 0x10, arg0 + 0x9C) >= 0) {
        *(s32 *)(arg0 + 0x34) = 0;
        *(s32 *)(arg0 + 0x30) = 0;
        *(s32 *)(arg0 + 0x2C) = 0;
        *(s32 *)(arg0 + 0x28) = 0;
        *(s32 *)(arg0 + 0x20) = 0;
        *(s16 *)(arg0 + 0x1C) = 0;
        *(s16 *)(arg0 + 0x26) = 0;
        *(s16 *)(arg0 + 0x24) = 0;
        *(s32 *)(arg0 + 0x50) = *(s8 *)(arg0 + 0xE);
        *(s32 *)(arg0 + 0x54) = *(s8 *)(arg0 + 0xF);
        *(s16 *)(arg0 + 0x98) = 2;
        *(s32 *)(arg0 + 0x5C) = *(s32 *)(arg0 + 0x3C);
        *(s32 *)(arg0 + 0x60) = *(s32 *)(arg0 + 0x40);
        *(s32 *)(arg0 + 0x58) = *(s32 *)(arg0 + 0x10);
        *(s32 *)(arg0 + 0x64) = *(s32 *)(arg0 + 0x44);
        *(s32 *)(arg0 + 0x8C) = 0;
        *(s32 *)(arg0 + 0x88) = 0;
        return (s16)(sp20);
    }
    return (s16)(0);
}
