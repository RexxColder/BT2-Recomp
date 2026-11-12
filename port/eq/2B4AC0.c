#include "common.h"

u8 *func_002B61E0(s32 arg0, s32 arg1, s32 arg2);

void func_002B4AC0(s32 arg0, s32 arg1, s32 arg2) {
    u8 *t = func_002B61E0(arg0, arg1, arg2);

    *(s32 *)(t + 0x30) = arg2;
    *(s32 *)(t + 0x28) = arg0;
    *(s32 *)(t + 0x2C) = arg1;
}
