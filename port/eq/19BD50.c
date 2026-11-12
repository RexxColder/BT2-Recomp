#include "common.h"

void EftPtcl3_SetPos(s32 arg0, s32 arg1);
void EftPtcl3_SetDir(s32 arg0, s32 arg1);

void func_0019BD50(u8 *arg0) {
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s3;
    u8 *temp_s4;
    s32 temp_a1;
    s32 var_s2;
    s32 var_s5;

    var_s5 = 0;
    temp_s4 = (u8 *)*(s32 *)(arg0 + 0x38);
    var_s3 = temp_s4;
    do {
        var_s1 = temp_s4;
        var_s0 = var_s3 + 0x10;
        var_s2 = 1;
        do {
            var_s2 -= 1;
            EftPtcl3_SetPos(*(s32 *)var_s0, (s32)(var_s1 + 0x40));
            temp_a1 = (s32)(var_s1 + 0x60);
            var_s1 += 0x10;
            EftPtcl3_SetDir(*(s32 *)var_s0, temp_a1);
            var_s0 += 0xC;
        } while (var_s2 >= 0);
        var_s5 += 1;
        var_s3 += 4;
    } while (var_s5 < 3);
}
