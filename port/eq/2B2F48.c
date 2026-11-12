#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
               f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);
extern u8 D_00377D50[] __attribute__((section(".data")));

s32 func_002B2F48(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7) {
    s32 var_v1 = 1;

    if (arg0 != 1) {
        var_v1 = 2;
        if (arg0 != 0 && arg0 != 2) {
            var_v1 = 3;
            if (arg0 != 3) {
                Rand_Range((s32)D_00377D50, arg1, arg2, arg3, arg4, arg5, arg6, arg7,
                           farg0, farg1, farg2, farg3, farg4, farg5, farg6, farg7);
                var_v1 = 3;
            }
        }
    }
    return var_v1;
}
