#include "common.h"

u8 *func_00101A88(s32 arg0);

void func_00101AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *t = func_00101A88(arg0);

    *(s8 *)(t + 0x1C4) = (s8)(arg2 & 0xFF);
    *(s32 *)(t + 0) = arg1;
    *(s32 *)(t + 0x1C0) = arg3;
}
