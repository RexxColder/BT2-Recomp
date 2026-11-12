#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002CF170(s32 arg0, s32 arg1);
s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002CEF30(u8 *arg0, s32 arg1) {
    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, 0xFF00013B);
        return;
    }
    if (func_002CF170((s32)arg0, 2) == 0) {
        *(s32 *)(arg0 + 0x96C) = *(s32 *)(arg0 + 0x96C) + 1;
        func_002D2FC8((s32)arg0, 6, 0xC, 0, arg1);
    }
}
