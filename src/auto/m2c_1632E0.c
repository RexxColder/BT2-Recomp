#include "m2c_macros.h"

s32 EftShot_TestBits(s32, M2C_UNK);                 /* extern */
M2C_UNK func_001633B8(s32 *, s32, s32);             /* extern */

void func_001632E0(s32 *arg0, s32 arg1) {
    s32 *var_s2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s3;

    var_s0 = 2;
    var_s2 = arg0;
    var_s3 = arg1;
    var_s1 = *var_s2;
    var_s0 = (EftShot_TestBits(var_s1, 2) == 0) ? 0 : 2;
    var_s0 = (EftShot_TestBits(var_s1, 4) != 0) ? (var_s0 | 4) : var_s0;
    var_s0 = (EftShot_TestBits(var_s1, 8) != 0) ? (var_s0 | 8) : var_s0;
    var_s0 = (EftShot_TestBits(var_s1, 0x10) != 0) ? (var_s0 | 0x10) : var_s0;
    var_s0 = (EftShot_TestBits(var_s1, 0x20) != 0) ? (var_s0 | 0x20) : var_s0;
    var_s0 = (EftShot_TestBits(var_s1, 0x40) != 0) ? (var_s0 | 0x40) : var_s0;
    func_001633B8(var_s2, var_s3, (EftShot_TestBits(var_s1, 0x80) == 0) ? var_s0 : (var_s0 | 0x80));
}
