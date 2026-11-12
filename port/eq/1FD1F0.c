#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);

s32 func_001FD1F0(void *arg0) {
    s32 r;
    s32 res;

    if (*(s32 *)((u8 *)arg0 + 0x1528) > 0) {
        return 9;
    }
    if (func_00211310((s32)arg0, 3, 0x200000) != 0) {
        return 8;
    }
    r = BtlObjXf_Update((s32)arg0);
    if (r < 0x106) {
        if (r >= 0x104) {
            return 5;
        }
        if (r >= 0x102) {
            return 4;
        }
        if (r >= 0x100) {
            return 1;
        }
        if (r == 0xFD) {
            return 6;
        }
        return 0;
    }
    if (r < 0x10A) {
        if (r < 0x108) {
            return 2;
        }
        return 3;
    }
    if (r == 0x10D) {
        res = func_00217488((s32)arg0);
        if (res >= 0x68) {
            return 0;
        }
        if (res >= 0x66) {
            return 7;
        }
        return 0;
    }
    if (r < 0x10E) {
        if (r == 0x10B) {
            return 1;
        }
        return 0;
    }
    if (r == 0x192) {
        return 8;
    }
    return 0;
}
