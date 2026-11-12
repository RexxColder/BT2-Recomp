#include "common.h"

void func_002C8D80(u8 *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    u8 *p = arg0 + 0xA0C;

    *arg3 = *(s32 *)(p + 0xAC);
    *arg2 = *(s32 *)(p + 0xA8);
}
