#include "common.h"

s32 func_00211288(u32 arg0);
s32 func_00217488(s32 arg0);
s32 func_002ADFC8(s32 arg0);
s32 func_002B1DD0(u32 arg0);
extern s32 D_00387930;
extern s32 D_00387E18;

s32 func_00209C18(u32 arg0) {
    s32 t;

    if (D_00387930 != 0 && arg0 < 2U) {
        t = func_00217488(func_00211288(arg0));
        if (t == 0x14) {
            return 4;
        }
        if (t < 0x15) {
            if (t == 0x10) {
                return 1;
            }
            if (t < 0x11) {
                if (t == 0xF) {
                    return 2;
                }
                return 0;
            }
            if (t == 0x13) {
                return 3;
            }
            return 0;
        }
        if (t == 0x33) {
            return 1;
        }
        if (t < 0x34) {
            if (t == 0x32) {
                return 3;
            }
            return 0;
        }
        if (t >= 0xC1 && t < 0xC4) {
            return 5;
        }
        return 0;
    }
    if (D_00387E18 != 0 && arg0 < 3U && func_002ADFC8(func_002B1DD0(arg0)) == 3) {
        return 1;
    }
    return 0;
}
