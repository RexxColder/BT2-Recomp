#include "common.h"

s32 func_002C61C0(s32 arg0, s32 arg1);
void func_002C6230(s32 arg0, s32 arg1);
s32 func_002CAC18(s32 arg0);
void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);

void func_002C6138(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_002CAC18(arg0);
    if ((temp_v0 == -1) || (func_002C61C0(arg0, temp_v0) != 0)) {
        func_002C6230(arg0, 1);
        if (*(s32 *) (arg0 + 0x950) == 0) {
            func_002D05E8(arg0, 5, 0);
        }
    }
}
