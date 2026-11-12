#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);

void func_002CF870(u8 *arg0, s32 arg1) {
    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, (s32)0xFF000152U);
        return;
    }
    *(s32 *)(*(u8 **)(arg0 + 0x36B0) + 0xDC0) = arg1;
}
