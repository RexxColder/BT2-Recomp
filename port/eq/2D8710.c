#include "common.h"

s32 func_002D87D8(s32 arg0);
s32 memcmp(void *arg0, void *arg1, u32 arg2);
extern u8 D_0037ADF8[] __attribute__((section(".data")));
extern u8 D_0037AE68[] __attribute__((section(".data")));

void func_002D8710(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = arg0;
    *arg3 = 0;
    *arg2 = 0;
    if ((var_s0 != 0) && (arg1 > 0)) {
        var_s1 = arg1;
        do {
            if ((memcmp((void *)var_s0, D_0037AE68, 1) == 0) && (memcmp((void *)var_s0, D_0037ADF8, 8) == 0)) {
                *arg2 = var_s0;
                *arg3 = func_002D87D8(var_s0);
            }
            var_s1 -= 1;
            var_s0 += 1;
        } while (var_s1 != 0);
    }
}
