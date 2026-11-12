#include "common.h"

void EftPtcl3_SetDir(s32 arg0, s32 arg1);
void EftPtcl3_SetPos(s32 arg0, s32 arg1);

void func_001CD7B0(u8 *arg0) {
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;

    var_s6 = 0;
    temp_v0 = *(s32 *)(arg0 + 0x38);
    var_s3 = temp_v0;
    var_s4 = var_s3;
    do {
        var_s1 = var_s3 + 0xC0;
        var_s0 = (s32 *)(var_s4 + 0x10);
        var_s2 = 1;
        do {
            temp_a1 = var_s1;
            var_s2 -= 1;
            var_s1 += 0x10;
            EftPtcl3_SetPos(*var_s0, temp_a1);
            temp_a0 = *var_s0;
            var_s0 += 1;
            EftPtcl3_SetDir(temp_a0, temp_v0 + 0x100);
        } while (var_s2 >= 0);
        var_s6 += 1;
        var_s4 += 8;
        var_s3 += 0x20;
    } while (var_s6 < 2);
}
