#include "common.h"

s32 strncmp(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0039D93C[] __attribute__((section(".data")));

s32 func_002F9860(s32 arg0, s32 arg1) {
    s32 var_s0;
    s32 var_s1;
    s32 var_a1;

    var_s0 = 0;
    var_s1 = (s32)D_0039D93C;
    var_a1 = (s32)D_0039D93C;
    for (;;) {
        var_s1 += 0x10;
        var_s0 += 1;
        if (strncmp(arg0, var_a1, arg1) == 0) {
            return 1;
        }
        var_a1 = var_s1;
        if (var_s0 >= 0x20) {
            return 0;
        }
    }
}
