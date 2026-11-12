#include "m2c_macros.h"

extern void *D_00387A40;

void func_00206E60(void *arg0, s32 arg1, s32 arg2) {
    u8 *base = (u8 *)arg0;

    if (*(s32 *)(base + 0x142C) < 0) {
        *(s32 *)(base + 0x142C) = arg1;
        *(s32 *)(base + 0x1428) = arg2;
        *(s8 *)(base + 0x1434) = 1;
        *(s32 *)(base + 0x1430) = *(s32 *)(*(u8 **)((u8 *)D_00387A40 + 8) + arg1 * 0x1520 + 0x10);
    }
}
