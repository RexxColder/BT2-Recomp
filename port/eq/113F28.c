#include "common.h"

void func_00113EC0(s32 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

void func_00113F28(s32 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    s32 *var_s0;

    if (!(*arg0 & 2)) {
        var_s0 = arg0;
        do {
            if (*var_s0 & 1) {
                func_00113EC0(var_s0, arg1, arg2, arg3, arg4);
            }
            var_s0 = (s32 *)((u8 *)var_s0 + 0x60);
        } while (!(*var_s0 & 2));
    }
}
