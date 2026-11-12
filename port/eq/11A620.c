#include "common.h"

s32 ColObb_Overlaps(s32 arg0, s32 arg1);
s32 ColSphere_ContactObb(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_0011A620(u8 *arg0, u8 **arg1) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;
    s32 var_s4;

    var_s4 = 0;
    if (*(s32 *)(arg0 + 0x3550) > 0) {
        var_s2 = arg0;
loop_2:
        var_s0 = arg1[0];
        var_s1 = var_s2;
loop_3:
        if (ColSphere_ContactObb((s32)(var_s1 + 0x1540), (s32)(var_s0 + 0x40), (s32)sp, (s32)sp10, (s32)sp20) != 0) {
            return 1;
        }
        var_s0 += 0x1D0;
        if (*(s32 *)var_s0 & 1) {
            var_s4 += 1;
            var_s2 += 0x20;
            if (var_s4 < *(s32 *)(arg0 + 0x3550)) {
                goto loop_2;
            }
        } else {
            goto loop_3;
        }
    }
    var_s4 = 0;
    if (*(s32 *)(arg0 + 0x3554) > 0) {
        var_s2 = arg0;
loop_8:
        var_s0 = arg1[0];
        var_s1 = var_s2;
loop_9:
        if (ColObb_Overlaps((s32)(var_s1 + 0x17A0), (s32)(var_s0 + 0x40)) != 0) {
            return 1;
        }
        var_s0 += 0x1D0;
        if (*(s32 *)var_s0 & 1) {
            var_s4 += 1;
            var_s2 += 0x190;
            if (var_s4 < *(s32 *)(arg0 + 0x3554)) {
                goto loop_8;
            }
        } else {
            goto loop_9;
        }
    }
    return 0;
}
