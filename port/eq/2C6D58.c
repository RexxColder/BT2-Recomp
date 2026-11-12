#include "common.h"

s32 func_002C0178(s32 arg0, s32 arg1, s32 *arg2);

void func_002C6D58(s32 arg0, s32 arg1) {
    s32 out[2];

    if (func_002C0178(arg0, *(s32 *)((u8 *)arg0 + 0x1FC8), out) != 0) {
        *(s32 *)((u8 *)arg1 + 4) = 0;
        *(s32 *)((u8 *)arg1 + 0) = 0;
        return;
    }
    *(s32 *)((u8 *)arg1 + 0) = out[0];
    *(s32 *)((u8 *)arg1 + 4) = out[1];
}
