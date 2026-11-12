#include "common.h"

/* 0x002D4188: returns 1 when func_002D07B0(a0, 15) is nonzero, else (func_002D26A8(a0) != 0). */
s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D26A8(s32 arg0);

s32 func_002D4188(s32 a0) {
    if (func_002D07B0(a0, 15) != 0) {
        return 1;
    }
    return func_002D26A8(a0) != 0;
}
