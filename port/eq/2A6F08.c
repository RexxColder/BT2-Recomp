#include "common.h"

s32 Gsc_GetInt(s32 arg0);
void func_002565C0(s32 arg0);
void func_002565E0(s32 arg0);
void func_00256C58(s32 arg0);
s32 func_00256DD0(void);

s32 func_002A6F08(s32 arg0) {
    s32 s0;

    s0 = 0;
    if (arg0 == 1) {
        return s0;
    }
    if (arg0 == 0) {
        func_00256C58(Gsc_GetInt(arg0));
        return s0;
    }
    if (arg0 == 2) {
        func_002565C0(arg0);
        if (func_00256DD0() != 0) {
            s0 = 1;
        }
        return s0;
    }
    if (arg0 == 3) {
        func_002565E0(arg0);
        return s0;
    }
    return 0;
}
