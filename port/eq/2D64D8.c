#include "common.h"

void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0037AB30[];

void func_002D64D8(s32 arg0, u8 *arg1, u8 *arg2) {
    u32 kind;

    kind = *(u32 *)(arg1 + 0);
    if (kind == 1 || kind == 2) {
        *(u32 *)(arg2 + 0) = 1U;
        *(s32 *)(arg2 + 4) = *(s32 *)(arg1 + 4);
        *(s32 *)(arg2 + 8) = *(s32 *)(arg1 + 0x44);
        *(s32 *)(arg2 + 0xC) = *(s32 *)(arg1 + 0xC);
        *(s32 *)(arg2 + 0x10) = *(s32 *)(arg1 + 8);
        return;
    }
    if (kind == 3) {
        *(u32 *)(arg2 + 0) = 3;
        *(s32 *)(arg2 + 4) = *(s32 *)(arg1 + 4);
        *(s32 *)(arg2 + 8) = *(s32 *)(arg1 + 0x44);
        *(s32 *)(arg2 + 0x14) = *(s32 *)(arg1 + 0x14);
        *(s32 *)(arg2 + 0xC) = *(s32 *)(arg1 + 0xC);
        *(s32 *)(arg2 + 0x24) = *(s32 *)(arg1 + 0x24);
        *(s32 *)(arg2 + 0x10) = *(s32 *)(arg1 + 8);
        *(s32 *)(arg2 + 0x18) = *(s32 *)(arg1 + 0x44) / 2;
        *(s32 *)(arg2 + 0x1C) = *(s32 *)(arg1 + 0x1C);
        *(s32 *)(arg2 + 0x20) = *(s32 *)(arg1 + 0x18);
        *(s32 *)(arg2 + 0x28) = *(s32 *)(arg1 + 0x44) / 2;
        *(s32 *)(arg2 + 0x2C) = *(s32 *)(arg1 + 0x2C);
        *(s32 *)(arg2 + 0x30) = *(s32 *)(arg1 + 0x28);
        return;
    }
    func_002D6C90(arg0, (s32)arg1, (s32)D_0037AB30);
}
