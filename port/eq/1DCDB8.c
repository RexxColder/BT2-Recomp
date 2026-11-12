#include "common.h"

s32 EftPtcl3_IsAlive(s32 arg0);

s32 func_001DCDB8(u8 *arg0) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s4;
    s32 var_s5;
    u8 *temp_s3;
    u8 *var_s2;

    var_s4 = 0;
    var_s5 = 0;
    temp_s3 = (u8 *)*(s32 *)(arg0 + 0x38);
    var_s2 = temp_s3;
    do {
        var_s1 = 0;
        var_s0 = (s32 *)(var_s2 + 0x10);
        do {
            if (*(s32 *)(temp_s3 + 0x240) != var_s1) {
                if (EftPtcl3_IsAlive(*var_s0) == 0) {
                    *var_s0 = 0;
                } else {
                    var_s5 = 1;
                }
            }
            var_s1 += 1;
            var_s0 += 1;
        } while (var_s1 < 9);
        var_s4 += 1;
        var_s2 += 4;
    } while (var_s4 <= 0);
    return var_s5;
}
