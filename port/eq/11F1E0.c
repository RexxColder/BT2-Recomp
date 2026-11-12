#include "common.h"

s32 EftObj_UpdateMtx(s32 arg0);
s32 func_0011ECA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0011FBC8(s32 arg0, s32 arg1);
void func_0011FD48(s32 arg0);

void func_0011F1E0(s32 arg0) {
    u8 *temp_s1;

    temp_s1 = (u8 *)arg0 + 0x38;
    if (func_0011FBC8(arg0, *(s32 *)(temp_s1 + 0x11C)) == 0 &&
        func_0011ECA8(arg0, EftObj_UpdateMtx(arg0), *(s32 *)(temp_s1 + 0x11C), 0x10) == 0) {
        func_0011FD48(arg0);
    }
}
