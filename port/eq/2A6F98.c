#include "common.h"

s32 Gsc_GetInt();
void func_001018E8(s32 arg0, s32 arg1);
void func_00259F98(s32 arg0, s32 arg1);
void func_0025A038(s32 arg0);
s32 func_002A0010(s32 arg0);
extern s32 D_003B0C34;

s32 func_002A6F98(s32 arg0, s32 *arg1) {
    s32 var_a0;
    s32 temp_s0;
    s32 temp_s1;
    s32 r2;

    temp_s1 = 0;
    if (arg0 == 1) {
        func_0025A038(1);
        return temp_s1;
    }
    if (arg0 == 0) {
        *arg1 = 0;
        temp_s0 = Gsc_GetInt(arg0);
        r2 = Gsc_GetInt();
        func_00259F98(temp_s0, r2);
        temp_s1 = func_002A0010(0x77) == 0;
        if (temp_s0 >= 0x164) {
            var_a0 = 0x854;
            if (temp_s0 >= 0x16B && temp_s0 == 0x3E8) {
                var_a0 = 0x852;
            }
        } else {
            var_a0 = 0x854;
        }
        func_001018E8(var_a0, 0);
        return temp_s1;
    }
    if (arg0 == 2) {
        if (*arg1 != 0) {
            temp_s1 = 1;
        } else if (D_003B0C34 & 0x4000) {
            *arg1 = 1;
        }
        return temp_s1;
    }
    return 0;
}
