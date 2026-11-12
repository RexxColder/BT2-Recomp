#include "common.h"

u8 *func_002C5478(u8 *arg0);

void func_002C4F00(u8 *arg0) {
    s64 temp_a0;
    u8 *temp_v0;
    u8 *temp_a2;
    u8 *temp_a3;
    u8 *temp_t0;

    temp_v0 = func_002C5478(arg0);
    temp_a3 = arg0 + 0xD30;
    if (temp_v0 != NULL) {
        temp_a2 = *(u8 **)(arg0 + 0x1F7C);
        temp_a0 = *(s64 *)(temp_a2 + 0x18);
        temp_t0 = arg0 + 0x90C;
        if (temp_a0 != 0x7FFFFFFFFFFFFFFFLL) {
            *(s64 *)(temp_a3 + 0x158) = temp_a0 - *(s64 *)(temp_v0 + 0x20);
            if (*(s32 *)temp_v0 == 0) {
                *(s64 *)(temp_v0 + 0x18) = *(s64 *)(temp_a3 + 0x150);
                *(s32 *)(temp_v0 + 4) = *(s32 *)(temp_t0 + 0x18) * 0x32;
                *(s64 *)(temp_v0 + 0x20) = *(s64 *)(temp_a2 + 0x10);
                *(s32 *)(temp_v0 + 8) = *(s32 *)(temp_t0 + 0x1C);
                *(s32 *)(temp_v0 + 0xC) = *(s32 *)(temp_a2 + 4);
                *(s32 *)(temp_v0 + 0x10) = *(s32 *)(temp_a2 + 8);
                *(s32 *)(temp_v0 + 0x28) = *(s32 *)(temp_a2 + 0x2C);
                *(s32 *)(temp_v0 + 0x2C) = *(s32 *)(temp_a2 + 0x30);
            }
        }
    }
}
