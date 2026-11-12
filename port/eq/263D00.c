#include "common.h"

extern u8 *D_003876A0;

void func_00263D00(u8 *arg0, f32 farg0, f32 farg1) {
    f32 var_f1;
    f32 temp_f0;
    s32 temp_v1;

    var_f1 = 1.0f;
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 46))) {
        temp_v1 = *(s32 *)arg0;
        if (temp_v1 & 0x40000000) {
            *(f32 *)(arg0 + 0x34) = 128.0f;
            return;
        }
        if (temp_v1 >= 0) {
            temp_f0 = *(f32 *)(arg0 + 0x3C);
            if (!(farg1 < temp_f0)) {
                if (farg0 < temp_f0) {
                    var_f1 = (temp_f0 - farg0) / (farg1 - farg0);
                } else {
                    var_f1 = 0.0f;
                }
            }
            *(f32 *)(arg0 + 0x34) = var_f1 * 128.0f;
            return;
        }
        *(f32 *)(arg0 + 0x34) = 0.0f;
        return;
    }
    *(f32 *)(arg0 + 0x34) = 0.0f;
}
