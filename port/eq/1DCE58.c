#include "common.h"

void EftPtcl3_Stop(s32 arg0);

void func_001DCE58(s32 arg0) {
    s32 temp_s3;
    s32 var_s2;
    s32 var_s1;

    temp_s3 = *(s32 *)(arg0 + 0x38);
    var_s2 = temp_s3;
    /* the outer loop runs once: its counter goes 0 -> 1 and blez fails */
    var_s1 = 0;
    while (var_s1 < 9) {
        if (*(s32 *)(temp_s3 + 0x240) != var_s1) {
            EftPtcl3_Stop(*(s32 *)(var_s2 + 0x10 + var_s1 * 4));
        }
        var_s1 += 1;
    }
}
