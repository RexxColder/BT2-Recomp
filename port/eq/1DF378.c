#include "common.h"

s32 func_00207EC0(s32 arg0);
extern u8 D_003B0690[] __attribute__((section(".data")));

s32 func_001DF378(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 temp_r;
    s32 temp_v1;

    var_s0 = (s32)D_003B0690 + 0x34;
    var_s1 = 0;
    var_s2 = (s32)D_003B0690;
    for (;;) {
        temp_r = func_00207EC0(arg0);
        temp_v1 = *(s32 *)var_s0;
        var_s0 += 0x40;
        if (temp_v1 == temp_r) {
            return var_s2;
        }
        var_s1 += 1;
        var_s2 += 0x40;
        if (var_s1 >= 7) {
            return 0;
        }
    }
}
