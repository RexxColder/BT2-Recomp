#include "common.h"

void func_002BF120(s32 arg0, u8 *arg1, s32 arg2);

void func_002BF0D8(u8 *arg0, s32 arg1) {
    u8 *v1 = *(u8 **)(arg0 + 0x2004);

    if (arg1 != 0 || *(s32 *)(v1 + 0x2C) != 1) {
        func_002BF120(*(s32 *)(v1 + 0), arg0 + 0x1020, arg1);
    }
}
