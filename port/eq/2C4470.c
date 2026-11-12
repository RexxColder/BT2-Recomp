#include "common.h"

s32 func_002C4518(void *arg0, s32 arg1, s32 arg2);
extern s32 D_00346E50 __attribute__((section(".data")));

s32 func_002C4470(void **arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;
    s32 var_v0;
    s32 (*vfn)(void *, s32);

    var_v0 = 0;
    vfn = *(s32 (**)(void *, s32))((u8 *)(*arg0) + 0x24);
    if (vfn(arg0, 0) >= arg2) {
        var_v0 = func_002C4518(arg0, arg1, arg2);
        temp_s0 = arg2 - var_v0;
        if (var_v0 != 0) {
            if ((temp_s0 > 0) && (func_002C4518(arg0, arg1 + var_v0, temp_s0) != temp_s0)) {
                D_00346E50 += 1;
            }
            var_v0 = 1;
        }
    }
    return var_v0;
}
