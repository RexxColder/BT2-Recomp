#include "common.h"

s32 func_002D1800(s32 arg0, s32 arg1, s32 arg2);
void func_002BED98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002BECD8(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 sp[2];
    u8 *temp_s1;
    s32 temp_s2;
    s32 var_a0;
    s32 var_v0;

    temp_s1 = *(u8 **)((u8 *)arg0 + 0x2004);
    temp_s2 = *(s32 *)temp_s1;
    var_v0 = func_002D1800(arg0, (s32)arg1, (s32)arg2);
    if (var_v0 != 0) {
        if (*(s32 *)((u8 *)arg0 + 0x48) != 4) {
            var_a0 = *(s32 *)(temp_s1 + 0x24);
        } else {
            func_002BED98(arg0 + 0x1020, temp_s2, (s32)sp, (s32)&sp[1]);
            var_a0 = *(s32 *)(temp_s1 + 0x24);
            if (var_a0 < sp[0]) {
                *(s32 *)(temp_s1 + 0x24) = sp[0];
                var_a0 = sp[0];
                *(s32 *)(temp_s1 + 0x28) = sp[1];
            }
        }
        *arg1 = var_a0;
        var_v0 = 0;
        *arg2 = *(s32 *)(temp_s1 + 0x28);
    }
    return var_v0;
}
