#include "common.h"

void func_002CB340(s32 arg0);
void func_002CB2D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0032ECA0(s32 arg0);
void func_0032EC80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002CB948(s32 arg0) {
    func_0032ECA0(*(s32 *)(arg0 + 0x40));
    *(s32 *)(arg0 + 0x44) = 0;
    func_002CB340(5);
    *(s32 *)(arg0 + 0x1C) = *(s32 *)0x1000B410;
    *(s32 *)(arg0 + 0x20) = *(s32 *)0x1000B430;
    *(s32 *)(arg0 + 0x24) = *(s32 *)0x1000B420;
    *(s32 *)(arg0 + 0x28) = *(s32 *)0x1000B400;
    while (*(volatile s32 *)0x10002010 & 0xF0) {
    }
    func_002CB2D8(0, 0x1000B420, 0x1000B400, 0x10002010);
    *(s32 *)(arg0 + 0x2C) = *(s32 *)0x1000B010;
    *(s32 *)(arg0 + 0x30) = *(s32 *)0x1000B020;
    *(s32 *)(arg0 + 0x34) = *(s32 *)0x1000B000;
    *(s32 *)(arg0 + 0x38) = *(s32 *)0x10002020;
    *(s32 *)(arg0 + 0x3C) = *(s32 *)0x10002010;
    func_0032EC80(*(s32 *)(arg0 + 0x40), 0x10002010, 0x1000B000, 0x10002020);
    return 1;
}
