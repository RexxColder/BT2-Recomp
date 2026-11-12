#include "common.h"

s32 func_002A20D0(u8 *arg0, s32 arg1);
extern u8 *D_00387EDC;

s32 Font_FindGlyph(s32 arg0, u8 **arg1) {
    u8 *var_s0;
    s32 temp_s2;
    s32 var_s1;
    s32 var_v1;

    var_v1 = 0;
    var_s0 = D_00387EDC;
    var_s1 = 0;
    temp_s2 = arg0 & 0xFFFF;
    while (var_s1 < 8) {
        var_s1 += 1;
        if (*(s32 *)var_s0 != 0) {
            var_v1 = func_002A20D0(var_s0, temp_s2);
            if (var_v1 != 0) {
                if (arg1 != NULL) {
                    *arg1 = var_s0;
                }
                break;
            }
        }
        var_s0 += 0x14;
    }
    if (var_v1 == 0 && temp_s2 == 0xA0) {
        var_v1 = Font_FindGlyph(0x20, arg1);
    }
    return var_v1;
}
