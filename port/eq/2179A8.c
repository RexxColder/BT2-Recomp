#include "common.h"

s32 func_00210D98(u8 *arg0, f32 farg0);
f32 func_0023F5E0(u8 *arg0);
f32 func_0023F6A8(u8 *arg0);
extern f32 D_00385B18;
extern f32 D_00385B1C;
extern f32 D_00385B20;

s32 func_002179A8(u8 *arg0, f32 farg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f3;
    f32 var_f1;
    f32 var_f20;
    s32 temp_s0;
    s32 var_v0;

    temp_s0 = func_00210D98(arg0, farg0) >> 7;
    var_f20 = func_0023F5E0(arg0);
    var_f1 = func_0023F6A8(arg0);
    var_v0 = 1;
    if (temp_s0 & 1) {
        var_f20 *= D_00385B1C;
        var_f1 *= D_00385B1C;
    }
    temp_f3 = *(f32 *)(arg0 + 0x101C);
    temp_f0 = temp_f3 + var_f20;
    *(f32 *)(arg0 + 0x101C) = temp_f0;
    if (D_00385B18 < temp_f0) {
        *(f32 *)(arg0 + 0x101C) = D_00385B18;
    }
    temp_f0_2 = *(f32 *)(arg0 + 0x1020) + var_f1;
    *(f32 *)(arg0 + 0x1020) = temp_f0_2;
    if (D_00385B20 < temp_f0_2) {
        *(f32 *)(arg0 + 0x1020) = D_00385B20;
    }
    if (!(temp_f3 < farg0) || !(farg0 <= *(f32 *)(arg0 + 0x101C))) {
        var_v0 = 0;
    }
    return var_v0;
}
