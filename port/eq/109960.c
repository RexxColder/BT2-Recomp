#include "common.h"

u16 *BtlText_NextLine(u16 *arg0);
u8 *func_001081D0(s32 arg0);

u8 *func_00109960(s32 arg0) {
    s32 var_s0;
    s32 var_s1;
    u16 *var_a0;
    u8 *var_s2;
    u8 *var_v0;
    s32 old;
    u16 temp_v0;

    var_s0 = arg0;
    var_s1 = 1;
    var_s2 = 0;
    var_a0 = (u16 *)(func_001081D0(arg0) + 2);
loop_1:
    var_v0 = var_s2;
    if (var_s1 != 0) {
        temp_v0 = var_a0[0];
        if (temp_v0 == 0x25) {
            if (var_a0[1] == 0x30) {
                old = var_s0;
                var_s0 -= 1;
                if (old <= 0) {
                    var_s1 = 0;
                    var_s2 = (u8 *)var_a0 + 4;
                }
            }
        } else if (temp_v0 == 0x40) {
            var_s1 = 0;
        }
        var_a0 = BtlText_NextLine(var_a0);
        var_v0 = var_s2;
        if (*var_a0 != 0) {
            goto loop_1;
        }
    }
    return var_v0;
}
