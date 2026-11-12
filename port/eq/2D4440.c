#include "common.h"

void func_002D4570(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D45D8(s32 arg0);
extern s32 D_00399D50 __attribute__((section(".data")));

s32 func_002D4440(s32 arg0, s32 arg1) {
    u8 *dd;
    s32 temp_s1;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;

    var_v0 = 0;
    var_s2 = 0;
    dd = (u8 *)&D_00399D50;
    temp_s1 = *(s32 *)(dd + 0);
    temp_s3 = *(s32 *)(dd + 8);
    if (*(s32 *)(dd + 4) < temp_s1) {
        var_s0 = 0;
        while (var_s0 < temp_s1) {
            temp_v0 = var_s0 * 0x10;
            var_s0 += 1;
            var_s2 = temp_s3 + temp_v0;
            if (func_002D45D8(var_s2) != 0) {
                break;
            }
        }
        func_002D4570(var_s2, arg0, arg1);
        var_v0 = var_s2;
        *(s32 *)(dd + 4) = *(s32 *)(dd + 4) + 1;
    }
    return var_v0;
}
