#include "common.h"

extern u8 *D_00387B04;
void sceVu0Normalize(s32 arg0, s32 arg1);

void func_00283770(s32 arg0, s32 arg1, s32 arg2) {
    s32 off = 48 * arg0;

    sceVu0Normalize((s32)(D_00387B04 + off), arg1);
    *(u8 *)(D_00387B04 + off + 0x28) = (u8)(arg2 & 0xFF);
}
