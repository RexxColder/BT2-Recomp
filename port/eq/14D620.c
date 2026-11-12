#include "common.h"

s32 func_001E7178(s32 arg0);

void func_0014D620(u8 *arg0, u8 **arg1) {
    u8 *temp_v0;
    u8 *temp_s7;
    u8 *var_s1;
    u8 *var_s3;
    s32 var_s2;
    s32 var_s5;
    s32 var_s6;
    u8 var_v1;

    temp_v0 = *arg1;
    var_s5 = 7;
    var_s6 = 1;
    temp_s7 = *(u8 **)(arg0 + 0x38);
    var_v1 = *(u8 *)(temp_v0 + 0x550);
    var_s3 = temp_s7 + 0xAB0;
    do {
        var_s2 = 0;
        if (var_v1 != 0) {
            var_s1 = var_s3;
            do {
                func_001E7178((s32)(var_s1 + 0x120));
                if (*(s32 *)(var_s1 + 0x120) != 0) {
                    var_s6 = 0;
                } else {
                    *(s32 *)var_s1 = 0;
                }
                var_v1 = *(u8 *)(temp_v0 + 0x550);
                var_s2 += 1;
                var_s1 += 4;
            } while (var_s2 < (s32)var_v1);
        }
        var_s5 -= 1;
        var_s3 += 0x140;
    } while (var_s5 >= 0);
    if (var_s6 == 1) {
        *(s8 *)(temp_s7 + 0xAA0) = 0;
    }
}
