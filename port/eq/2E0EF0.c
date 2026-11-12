#include "common.h"

void func_002E0EF0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p = arg0 + 8;
    *(s32 *)(p + 8) = arg2;
    *(s32 *)(p + 0) = arg3;
    *(s32 *)(p + 4) = arg1;
    *(s32 *)(arg0 + 4) = 1;
}
