#include "common.h"

s32 func_002D1070(u8 *arg0);
s32 func_002D1800(u8 *arg0, s32 arg1, s32 arg2);

s32 func_002D1708(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 sp[2];
    s32 (*temp_v0)(s32, s32 *, s32 *);
    s32 temp_s2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_s0;

    var_v0 = func_002D1800(arg0, (s32)arg1, (s32)arg2);
    temp_s0 = arg0 + 0xD30;
    if (var_v0 != 0) {
        temp_v0 = *(s32 (**)(s32, s32 *, s32 *))(temp_s0 + 0x2D4);
        if (temp_v0 != NULL) {
            temp_s2 = temp_v0(*(s32 *)(temp_s0 + 0x2E8), sp, &sp[1]);
            if (func_002D1070(arg0) != 0) {
                if (*(s32 *)(temp_s0 + 0x2D8) != -5) {
                    var_v1 = sp[0] - *(s32 *)(temp_s0 + 0x2D8);
                    if (var_v1 < 0) {
                        var_v1 = var_v1 + *(s32 *)(temp_s0 + 0x2E4) + 1;
                    }
                    *(s32 *)(temp_s0 + 0x2DC) = *(s32 *)(temp_s0 + 0x2DC) + var_v1;
                }
            }
            var_v0 = temp_s2;
            *(s32 *)(temp_s0 + 0x2D8) = sp[0];
            *(s32 *)(temp_s0 + 0x2E0) = sp[1];
            *arg1 = *(s32 *)(temp_s0 + 0x2DC);
            var_v1_2 = *(s32 *)(temp_s0 + 0x2E0);
        } else {
            var_v1_2 = 1;
            *arg1 = -2;
            var_v0 = 0;
        }
        *arg2 = var_v1_2;
    }
    return var_v0;
}
