#include "common.h"

extern s32 D_00346DE0;

void func_002D25B8(u8 *arg0, s32 *arg1, f32 f12, f32 f13) {
    f32 temp_f1;
    s32 var_t0;
    s32 var_v0;
    u8 *temp_a2;

    temp_f1 = (f32)*(s32 *)(arg0 + 0xAC4);
    temp_a2 = arg0 + 0xD30;
    if ((f13 + temp_f1) < f12) {
        *arg1 = 0;
        return;
    }
    if (f12 <= (f13 - temp_f1)) {
        *arg1 = 1;
        if ((*(f32 *)(temp_a2 + 0x2C8) != f12) && (*(f32 *)(temp_a2 + 0x2C0) != f12)) {
            *(f32 *)(temp_a2 + 0x2C0) = f12;
            *(s32 *)(temp_a2 + 0x2BC) = *(s32 *)(temp_a2 + 0x2BC) + 1;
        }
    } else {
        var_t0 = 0;
        if ((D_00346DE0 == 0xEA24) && (*(s32 *)(arg0 + 0x920) < 3)) {
            var_t0 = (*(s32 *)(temp_a2 + 0x2AC) == 0x3E8);
        }
        if (var_t0 >= *(s32 *)(temp_a2 + 0x2BC)) {
            var_v0 = *(s32 *)(temp_a2 + 0x2C4);
            *arg1 = var_v0;
        } else {
            var_v0 = 1;
            if (f13 < f12) {
                *arg1 = 0;
            } else {
                *arg1 = var_v0;
            }
        }
        *(s32 *)(temp_a2 + 0x2BC) = 0;
        *(f32 *)(temp_a2 + 0x2C8) = f12;
        *(s32 *)(temp_a2 + 0x2C4) = *arg1;
    }
}
