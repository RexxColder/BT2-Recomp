#include "common.h"

void func_002D6DD0(s32 arg0, s32 arg1, s32);

void func_002D6D70(s32 arg0, s32 arg1, s32 arg2) {
    func_002D6DD0(arg0, 0x64, arg2);
    *(s32 *)((u8 *)arg0 + arg1 * 4 + 0x38) = arg2;
}
