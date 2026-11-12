#include "common.h"

s32 func_002EA050(s32 arg0);
s32 func_002EBC78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_0037BDD0[] __attribute__((section(".data")));
extern u8 D_0037BDF8[] __attribute__((section(".data")));
extern u8 D_0037BE28[] __attribute__((section(".data")));

s32 func_002EBDD0(u8 *arg0, s32 arg1, s32 arg2) {
    s32 a3;
    s32 v0;

    if (arg0 == NULL) {
        func_002EA050((s32)D_0037BDD0);
        return -3;
    }
    if (arg1 < 0) {
        func_002EA050((s32)D_0037BDF8);
        return -3;
    }
    if (arg2 == 0) {
        func_002EA050((s32)D_0037BE28);
        return -3;
    }
    a3 = (s8)arg0[1];
    v0 = 0;
    if (a3 != 2) {
        v0 = func_002EBC78((s32)arg0, arg1, arg2, a3);
        arg0[2] = 1;
    }
    return v0;
}
