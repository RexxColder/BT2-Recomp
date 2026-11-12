#include "common.h"

s32 strlen(s32 arg0);
s32 func_002E70B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002E7C88(s32 arg0, s32 arg1) {
    u16 sp0;
    u16 sp2;
    u16 sp4;

    func_002E70B0(arg1, strlen(arg1), (s32)&sp0, (s32)&sp2, (s32)&sp4);
    *(u16 *)((u8 *)arg0 + 0xA0) = sp0;
    *(u16 *)((u8 *)arg0 + 0xA4) = sp4;
    *(u16 *)((u8 *)arg0 + 0xA2) = sp2;
}
