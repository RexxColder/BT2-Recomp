#include "common.h"

void func_001F9E38(u8 *arg0, s32 arg1) {
    s32 v = (arg1 < 0 ? arg1 + 7 : arg1) >> 3;
    u8 *p = arg0 + v + 0x8F4;

    *p = (u8)(*p | (1 << (arg1 - v * 8)));
}
