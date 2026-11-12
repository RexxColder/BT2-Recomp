#include "common.h"

/* 0x001FA0A0: r = func_001F9FB0(a0, a2); if (r) { func_001F9D78(a0, a1); func_002113C0(a0, 2, 1, 0); } return r & 0xFF. */
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001F9D78(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_001FA0A0(s32 a0, s32 a1, s32 a2) {
    s32 r;

    r = func_001F9FB0(a0, a2);
    if (r != 0) {
        func_001F9D78(a0, a1);
        func_002113C0(a0, 2, 1, 0);
    }
    return r & 0xFF;
}
