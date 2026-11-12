#include "common.h"

s32 SndHd_GetVagMax(s32 arg0);
void func_002981B8(s32 arg0, u8 *arg1);

void func_00298240(s32 arg0, u8 *arg1) {
    u8 sp[0x80];
    s32 temp_s1;
    s32 temp_v0;
    s32 var_a1;
    u8 *temp_v0_2;

    temp_s1 = SndHd_GetVagMax(arg0);
    func_002981B8(arg0, sp);
    var_a1 = 0;
    if (temp_s1 > 0) {
        do {
            if (sp[var_a1] & 1 & 0xFF) {
                temp_v0 = (s32)((var_a1 < 0) ? (var_a1 + 7) : var_a1) >> 3;
                temp_v0_2 = arg1 + temp_v0;
                *temp_v0_2 |= 1 << (var_a1 - (temp_v0 * 8));
            }
            var_a1 += 1;
        } while (var_a1 < temp_s1);
    }
}
