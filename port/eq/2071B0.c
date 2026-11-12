#include "common.h"

extern void *D_00387A40;

void func_002071B0(void *arg0, s32 arg1) {
    s32 temp_a0;
    u8 *temp_a0_2;

    temp_a0 = *(s32 *)((u8 *)arg0 + 0x142C);
    if (temp_a0 >= 0 && temp_a0 < *(s32 *)((u8 *)D_00387A40 + 0xC)) {
        temp_a0_2 = *(u8 **)((u8 *)D_00387A40 + 0x8) + temp_a0 * 0x1520;
        if (arg1 & 0xFF) {
            *(s32 *)(temp_a0_2 + 0xAF0) = *(s32 *)(temp_a0_2 + 0xAF0) | 0x10;
            return;
        }
        *(s32 *)(temp_a0_2 + 0xAF0) = *(s32 *)(temp_a0_2 + 0xAF0) & ~0x10;
    }
}
