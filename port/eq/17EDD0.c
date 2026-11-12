#include "common.h"

void func_0017E120(s32 arg0, s32 arg1, f32 farg0);

void EftBolt_DrawAll(s32 arg0, f32 farg0) {
    s32 var_s1;
    u8 *var_s0;

    var_s0 = (u8 *)arg0 + 0x10;
    var_s1 = 9;
    do {
        if (*(s32 *)(var_s0 + 0xC) & 1) {
            func_0017E120(arg0, (s32)var_s0, farg0);
        }
        var_s1 -= 1;
        var_s0 += 0x90;
    } while (var_s1 >= 0);
}
