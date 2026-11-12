#include "common.h"

s32 func_002B64F0(s32 arg0, s32 arg1, s32 arg2);

void func_002B53B0(u8 *arg0, u8 *arg1, u8 *arg2) {
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    u8 *temp_v0;
    u8 *var_s2;

    var_s2 = arg2;
    var_s3 = (s32)(arg0 + 0x160);
    temp_v0 = (u8 *)*(s32 *)(arg1 + 0x38);
    var_s4 = *(s32 *)(arg0 + 0x178);
    var_s1 = *(s32 *)(temp_v0 + 4);
    var_s0 = *(s32 *)(temp_v0 + 0);
    /* GUESS arity: a0..a2 are not written before this call, passed through */
    if ((func_002B64F0((s32)arg0, (s32)arg1, (s32)arg2) != 1) || (var_s4 == var_s3)) {
        *(s32 *)(var_s2 + 0x48) = 0;
        *(s32 *)(var_s2 + 0x44) = 0;
        return;
    }
    if ((var_s0 != 0) && (var_s1 >= 5)) {
        var_s0 += 4;
        var_s1 -= 4;
    }
    *(s32 *)(var_s2 + 0x48) = var_s1;
    *(s32 *)(var_s2 + 0x44) = var_s0;
}
