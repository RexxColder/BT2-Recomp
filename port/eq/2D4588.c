#include "common.h"

void IVec4_SetZero(s32 arg0);

void func_002D4588(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;

    if (arg0 > 0) {
        var_s1 = arg1;
        var_s0 = arg0;
        var_a0 = var_s1;
        do {
            var_s1 += 0x10;
            var_s0 -= 1;
            IVec4_SetZero(var_a0);
            var_a0 = var_s1;
        } while (var_s0 != 0);
    }
}
