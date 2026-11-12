#include "common.h"

void func_002D1510(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DA360(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002D26A8(u8 *arg0) {
    s32 sp[2];
    s32 temp_s0;
    s32 temp_s1;
    s32 var_v0;
    u8 *temp_v1;

    var_v0 = 1;
    temp_v1 = arg0 + 0xD30;
    temp_s0 = *(s32 *)(temp_v1 + 0x280);
    temp_s1 = *(s32 *)(temp_v1 + 0x27C);
    if (*(s32 *)(arg0 + 0x950) != 0) {
        var_v0 = 0;
        if (temp_s1 != -5) {
            func_002D1510((s32)arg0, (s32)&sp[0], (s32)&sp[1]);
            var_v0 = func_002DA360(temp_s1 + ((temp_s0 * 0x7D0) / 59940), temp_s0, sp[0], sp[1]) != 0;
        }
    }
    return var_v0;
}
