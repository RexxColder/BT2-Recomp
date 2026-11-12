#include "common.h"

s32 func_001EDB20(s32 arg0, s32 arg1);
void func_001EDBD8(s32 arg0, s32 arg1);
void func_001EDC20(s32 arg0, s32 arg1);
s32 func_001F3758(s32 arg0);

void func_00168EE8(s32 arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 6;
    temp_v1 = *(s32 *) (func_001F3758(arg0) + 0x38);
    var_s0 = *(s32 *) (arg0 + 0x38) + 0xAB0;
    var_a1 = *(s32 *) (temp_v1 + 0x1E80);
    do {
        var_s1 -= 1;
        temp_v0 = func_001EDB20(var_s0, var_a1);
        *(s32 *) (var_s0 + 0x30) = temp_v0;
        func_001EDBD8(temp_v0, 0);
        temp_a0 = *(s32 *) (var_s0 + 0x30);
        var_s0 += 0xF0;
        func_001EDC20(temp_a0, 0);
        if (var_s1 >= 0) {
            var_a1 = *(s32 *) (temp_v1 + 0x1E80);
        }
    } while (var_s1 >= 0);
}
