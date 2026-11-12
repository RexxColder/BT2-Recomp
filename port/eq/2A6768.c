#include "common.h"

s32 Gsc_GetInt();
void func_002611E8(s32 arg0, s32 arg1);
void func_00261468(s32 arg0, s32 arg1, s32 arg2);
s32 func_002615B0(u16 arg0);
s32 func_002A0010(s32 arg0);

s32 func_002A6768(s32 arg0, s32 *arg1) {
    s32 var_s5;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s4;
    s32 temp_v0;
    s32 var_s1;

    var_s1 = 0;
    switch (arg0) {
    case 0:
        var_s5 = 1;
        temp_s2 = Gsc_GetInt(arg0);
        temp_s0 = temp_s2 & 0xFFFF;
        temp_s4 = Gsc_GetInt();
        func_002611E8(temp_s0, 1);
        if (func_002A0010(0x6C) != 0) {
            var_s5 = 2;
            var_s1 = 1;
        }
        temp_v0 = func_002A0010(0x77);
        *arg1 = temp_s2;
        var_s1 = (temp_v0 == 0) ? 1 : var_s1;
        func_00261468(temp_s0, temp_s4, var_s5);
    case 1:
block_10:
        return var_s1;
    case 2:
        var_s1 = func_002615B0(*(u16 *)arg1) == 0;
        goto block_10;
    default:
        return 0;
    }
}
