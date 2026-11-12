#include "common.h"

s32 *func_00202E60(s32 arg0, s32 arg1);

void func_002031E0(u8 *arg0) {
    s32 temp_hi;
    s32 temp_v0;
    s32 var_a1;
    s32 var_s2;

    var_a1 = *(s32 *)(arg0 + 0x1184);
    var_s2 = 0;
    if (var_a1 > 0) {
loop_2:
        temp_v0 = *(s32 *)(arg0 + 0x118C) + var_s2;
        var_s2 += 1;
        temp_hi = (temp_v0 + 1) % var_a1;
        if (temp_hi != *(s32 *)(arg0 + 0x1180)) {
            if (*func_00202E60((s32)arg0, temp_hi) <= 0) {
                goto block_8;
            }
            *(s32 *)(arg0 + 0x118C) = temp_hi;
            return;
        }
block_8:
        var_a1 = *(s32 *)(arg0 + 0x1184);
        if (var_s2 < var_a1) {
            goto loop_2;
        }
    }
}
