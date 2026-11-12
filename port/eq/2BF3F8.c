#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002C3210(s32 arg0);
s32 func_002D07B0(s32 arg0, s32 arg1);

void func_002BF3F8(s32 arg0, s32 arg1) {
    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF0001A3);
        return;
    }
    if (func_002D07B0(arg0, 6) != 0) {
        ((void (*)(s32, s32))(*(s32 *)(*(s32 *)(arg0 + 0x2114) + 0xC)))(arg0, arg1);
    }
}
