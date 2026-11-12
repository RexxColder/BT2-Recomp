#include "common.h"

s32 func_002C0250(s32 arg0, s32 arg1, s32 arg2);

s32 func_002C9BB0(s32 arg0, s32 arg1) {
    return func_002C0250(arg0, *(s32 *)((u8 *)arg0 + 0x1FC8), arg1);
}
