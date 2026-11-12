#include "common.h"

s32 func_002D7108(s32 arg0, s32 arg1, s32 arg2);

void func_002D7080(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = (arg2 / 2) * 2;
    temp_v1 = (arg1 / 2) * 2;
    temp_s2 = temp_v1 / 2;
    temp_s1 = temp_v0 / 2;
    func_002D7108(arg0 + 4, temp_v0, temp_v1);
    func_002D7108(arg0 + 0x14, temp_s1, temp_s2);
    func_002D7108(arg0 + 0x24, temp_s1, temp_s2);
}
