#include "common.h"

s32 func_002C3210(void *arg0);
void func_002C2FF0(s32 arg0, s32 arg1);

void func_002D18B0(void *arg0, s32 arg1) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF000124);
        return;
    }
    *(s32 *)((u8 *)arg0 + 0xD48) = arg1;
}
