#include "common.h"

extern s32 D_00387A40;

void func_0025CDA0(s32 arg0, s32 arg1) {
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_t0;
    s32 limit;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    s32 ok;
    u8 *var_a0;

    temp_t1 = *(s32 *) (arg0 + 0x4C);
    var_a2 = 0;
    temp_v0 = *(s32 *) (arg0 + 0x44);
    temp_t0 = *(u8 *) (temp_v0 + 0x24);
    if (*(s32 *) temp_t1 == 0) {
        return;
    }
    limit = temp_t0 + *(u8 *) (temp_v0 + 0x25);
    var_a0 = (u8 *) (arg0 + 0xB85);
    var_a1 = (arg1 * 0x14) + 0x38081;
    var_v0 = temp_t0 > 0;
    do {
        if (var_v0 != 0) {
            var_a2 += 1;
        } else {
            ok = var_a2 < limit;
            var_a2 += 1;
            if (ok) {
                *var_a0 = *(u8 *) (D_00387A40 + var_a1 + 4);
                var_a1 += 1;
                var_a0 += 1;
            }
        }
        var_v0 = var_a2 < temp_t0;
    } while ((u32) var_a2 < *(u32 *) temp_t1);
}
