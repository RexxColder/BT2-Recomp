#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002C3210(u8 *arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002D07C0(u8 *arg0, u8 *arg1) {
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, (s32)0xFF000114);
    }
    memcpy(arg1, arg0 + 0x90C, 0x40);
    return 0;
}
