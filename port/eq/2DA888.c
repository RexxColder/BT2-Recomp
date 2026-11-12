#include "common.h"

s32 func_002DCC38(s32 arg0);

void func_002DA888(s32 arg0, s32 arg1, s32 arg2) {
    if (func_002DCC38(arg0) == 0) {
        *(s32 *)((u8 *)arg0 + 0xF0) = arg2;
        *(s32 *)((u8 *)arg0 + 0xEC) = arg1;
    }
}
