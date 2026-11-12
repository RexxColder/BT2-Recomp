#include "common.h"

void *memset(void *s, s32 c, u32 n);
s32 func_001805E0(s32 arg0);

void func_00180398(u8 *arg0, s32 arg1) {
    memset(arg0, 0, 0x80);
    *(s32 *)(arg0 + 0x7C) = arg1;
    *(s32 *)(arg0 + 0x78) = func_001805E0(arg1);
}
