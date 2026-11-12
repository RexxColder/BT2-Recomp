#include "common.h"

f32 func_00207F60(s32 arg0);
s32 func_00207EC0(s32 arg0);
extern f32 D_00384C88;
extern f32 D_00384C8C;

f32 func_001964F0(s32 arg0) {
    f32 temp_f20;
    f32 var_f0;
    f32 var_f0_2;
    s32 temp_v0;

    temp_f20 = func_00207F60(arg0);
    temp_v0 = func_00207EC0(arg0);
    if (temp_v0 < 0x47) {
        if (temp_v0 < 0x45) {
            if (temp_v0 != 0x1A) {
                if (temp_v0 < 0x1B) {
                    if (temp_v0 != 0x15) {
                        return temp_f20;
                    }
                    goto block_17;
                }
                if (temp_v0 != 0x3D) {
                    return temp_f20;
                }
                goto block_17;
            }
block_17:
            var_f0_2 = D_00384C8C;
            goto block_20;
        }
        goto block_15;
    }
    if (temp_v0 < 0x6E) {
        if (temp_v0 < 0x6A) {
            if (temp_v0 != 0x68) {
                return temp_f20;
            }
            var_f0_2 = 0.5f;
            goto block_20;
        }
        goto block_15;
    }
    var_f0 = temp_f20;
    if (temp_v0 == 0x79) {
block_15:
        var_f0_2 = D_00384C88;
block_20:
        var_f0 = temp_f20 * var_f0_2;
    }
    return var_f0;
}
