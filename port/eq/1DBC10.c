#include "common.h"

s32 func_001DBB68(s32 arg0, s32 arg1, s32 arg2);
void func_001DBC10(s32 arg0, s32 arg1, s32 arg2);

void func_001DBC10(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = arg1;
    while (var_s0 < arg2) {
        temp_v0 = func_001DBB68(arg0, var_s0, arg2);
        func_001DBC10(arg0, var_s0, temp_v0 - 1);
        var_s0 = temp_v0 + 1;
    }
}
