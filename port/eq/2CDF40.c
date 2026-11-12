#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002CDFD8(s32 arg0, s32 arg1);
s32 func_002CE040(void);
/* GUESS arity: only a0/a1 are passed; a2..a4 are leftovers after the earlier calls */
s32 func_002CE080(s32 arg0, s32 arg1);
extern s32 D_00346E2C[] __attribute__((section(".data")));

s32 func_002CDF40(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_v0;

    var_v0 = 0;
    if (func_002CDFD8(arg0, arg1) == 0) {
        var_s0 = func_002CE040();
        if (var_s0 == -1) {
            func_002C2FF0(0, 0xFF000206);
            return 0;
        }
        var_v0 = func_002CE080(arg0, arg1);
        D_00346E2C[var_s0] = var_v0;
        return var_v0;
    }
    return var_v0;
}
