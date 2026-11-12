#include "common.h"

s32 func_00276908(s32 arg0);
s32 func_00276D00(void);
extern u8 *D_003876A0;

s32 func_00132B50(s32 arg0) {
    s64 flags;
    u8 *s0;
    s32 s1;

    flags = *(s64 *)(D_003876A0 + 0x4D8);
    s0 = *(u8 **)(D_003876A0 + 4);
    if (flags & ((s64)0x8000 << 47)) {
        s0 = s0 + 0x40;
    }
    s1 = 1;

    if (arg0 > 0) {
        s1 = 0;
        if (func_00276908(arg0) != 0) {
            s1 = 1;
        }
        return s1;
    }
    if (arg0 == -1) {
        s1 = 0;
        if (func_00276908(7) == 0) {
            if (*(s32 *)(s0 + 0x4C) != *(s32 *)(s0 + 0x48)) {
                s1 = 1;
            }
            return s1;
        }
        return 0;
    }
    if (arg0 == -2) {
        s1 = 0;
        if (flags & 3) {
            s1 = 1;
        }
        return s1;
    }
    if (arg0 == -3) {
        s1 = 0;
        if (*(s32 *)(s0 + 0x38) != *(s32 *)(s0 + 0x34)) {
            s1 = 1;
        }
        return s1;
    }
    if (arg0 == -4) {
        s1 = 0;
        if (*(s32 *)(s0 + 0x3C) != *(s32 *)(s0 + 0x38)) {
            s1 = 1;
        }
        return s1;
    }
    if (arg0 == -5) {
        s1 = (func_00276D00() != 0);
        return s1;
    }
    return s1;
}
