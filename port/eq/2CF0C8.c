#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002CF170(s32 arg0, s32 arg1);
void func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_002CF0C8(u8 *arg0, s32 arg1) {
    s32 temp_v0;

    if (func_002C3210((s32)arg0) != 0) {
        func_002C2FF0(0, 0xFF000137);
        return;
    }
    if (func_002CF170((s32)arg0, 1) == 0) {
        temp_v0 = *(s32 *)(arg0 + 0x96C);
        if (temp_v0 < *(s32 *)(arg0 + 0x968)) {
            *(s32 *)(arg0 + 0x96C) = temp_v0 + 1;
        }
        func_002D2FC8((s32)arg0, 6, 0xC, arg1, 0);
    }
}
