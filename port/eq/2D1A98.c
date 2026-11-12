#include "common.h"

s32 func_002D1B20(s32 arg0);
extern s32 D_00346E2C[] __attribute__((section(".data")));

s32 func_002D1A98(s32 arg0) {
    s32 s2;
    s32 i;
    s32 v;
    s32 t;

    if (arg0 != 0) {
        return func_002D1B20(arg0);
    }
    s2 = 0;
    for (i = 0; i < 8; i++) {
        v = D_00346E2C[i];
        if (v != 0) {
            t = func_002D1B20(v);
            if (t != 0) {
                s2 = t;
            }
        }
    }
    return s2;
}
