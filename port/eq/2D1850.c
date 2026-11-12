#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);

void func_002D1850(u8 *arg0) {
    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, (s32)0xFF000122U);
        return;
    }
    *(s32 *)(arg0 + 0xD30 + 0x2A4) = *(s32 *)(arg0 + 0xD30 + 0x2A4) + 1;
    *(s32 *)(arg0 + 0x44) = 1;
}
