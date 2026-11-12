#include "common.h"

s32 func_002FEEF8(s32 arg0, s32 arg1);
extern u8 D_00356E98[] __attribute__((section(".data")));

void func_002FF578(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3) {
    s32 var_s0;
    u8 *var_s1;
    s32 temp_v0;

    var_s0 = 0;
    if (arg3 > 0) {
        var_s1 = arg2;
        do {
            temp_v0 = (*(s32 *)(D_00356E98 + 0xC) * var_s0) + var_s0;
            var_s0 += 1;
            if (func_002FEEF8(arg1, (s32)(arg2 + ((*(s32 *)(D_00356E98 + 8) * 8) + temp_v0))) == 0) {
                *(s32 *)arg0 = *(s32 *)var_s1;
                *(s32 *)(arg0 + 4) = *(s32 *)(var_s1 + 4);
                return;
            }
            var_s1 += 8;
        } while (var_s0 < arg3);
    }
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)arg0 = 0;
}
