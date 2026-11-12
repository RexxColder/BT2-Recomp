#include "common.h"

void func_002DA708(s32 arg0, s32 arg1, s32 arg2);

void func_002CE2B0(s32 arg0) {
    func_002DA708(arg0, 0, 0x10);
    *(s32 *)((u8 *)arg0 + 0x2C) = -1;
    *(s32 *)((u8 *)arg0 + 0x1C) = 1;
    *(s32 *)((u8 *)arg0 + 0x00) = 0;
    *(s32 *)((u8 *)arg0 + 0x04) = 0;
    *(s32 *)((u8 *)arg0 + 0x08) = 0;
    *(s32 *)((u8 *)arg0 + 0x0C) = 0;
    *(s32 *)((u8 *)arg0 + 0x10) = 0;
    *(s32 *)((u8 *)arg0 + 0x14) = 0;
    *(s32 *)((u8 *)arg0 + 0x18) = 0;
    *(s32 *)((u8 *)arg0 + 0x20) = 0;
    *(s32 *)((u8 *)arg0 + 0x24) = -1;
    *(s32 *)((u8 *)arg0 + 0x28) = -1;
}
