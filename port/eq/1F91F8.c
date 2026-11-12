#include "common.h"

void func_001F91F8(u8 *arg0) {
    s32 var_t3;
    s32 var_t8;
    s32 var_t1;
    s32 temp_v0;
    s32 var_a3;
    s32 *var_t0;
    u8 *var_t2;

    var_t3 = 0;
    var_t2 = arg0 + 0xB02;
    var_t8 = 0;
    do {
        var_t1 = 1;
        temp_v0 = (var_t8 + var_t3) * 4;
        var_a3 = temp_v0 + 0xAF0;
        var_t0 = (s32 *)(arg0 + 0x14 + temp_v0 + 0xAF0);
        do {
            arg0[8 + var_a3] = 0;
            arg0[0xA + var_a3] = 0;
            arg0[0xC + var_a3] = 0;
            arg0[0xE + var_a3] = 0;
            arg0[0x10 + var_a3] = 0;
            var_a3 += 1;
            var_t1 -= 1;
            *var_t0 = 0;
            var_t0 += 1;
        } while (var_t1 >= 0);
        var_t3 += 1;
        *var_t2 = 0;
        var_t8 += 4;
        var_t2 += 0x14;
    } while (var_t3 < 4);
}
