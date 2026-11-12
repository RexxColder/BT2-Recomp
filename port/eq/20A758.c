#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);
extern s32 D_00387930;

s32 func_0020A758(s32 arg0) {
    s32 t;

    if (D_00387930 == 0) {
        return 0;
    }
    if ((u32)arg0 >= 2) {
        return 0;
    }
    t = func_00217488(func_00211288(arg0));
    if (t < 0xC1) {
        return 0;
    }
    if (t < 0xC4) {
        return 1;
    }
    if (t >= 0xD0) {
        return 0;
    }
    if (t < 0xCD) {
        return 0;
    }
    return 1;
}
