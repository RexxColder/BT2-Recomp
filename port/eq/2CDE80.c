#include "common.h"

void func_002C32B0(s32 arg0, s32 arg1, s32 arg2);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00346DC0 __attribute__((section(".data")));
extern u8 *D_00346E2C __attribute__((section(".data")));

s32 func_002CDE80(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[8];
    u8 **var_a2;
    u8 *var_v0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s0_2;
    s32 temp_v0;

    func_002C32B0((s32)&sp[4], arg1, arg2);
    sp[0] = 0;
    sp[1] = 0;
    sp[2] = 0;
    var_a2 = (u8 **)&D_00346E2C;
    var_a1 = 7;
    var_v0 = D_00346E2C;
    for (;;) {
        var_a2 += 1;
        if (var_v0 != 0) {
            temp_v0 = *(s32 *)(var_v0 + 0x48);
            var_s0_2 = 0;
            if (temp_v0 != 0) {
                var_s0_2 = 2;
                if (temp_v0 != 6) {
                    var_s0_2 = 1;
                    if (temp_v0 < 0) {
                        var_s0_2 = 2;
                    }
                }
            }
            sp[var_s0_2] += 1;
        }
        var_a1 -= 1;
        if (var_a1 < 0) {
            break;
        }
        var_v0 = *var_a2;
    }
    var_s0 = 1;
    if (sp[1] == 0) {
        var_s0 = (sp[2] == 0) ? 0 : 2;
    }
    D_00346DC0 = var_s0;
    func_002C32C8((s32)&sp[4], var_a1, (s32)var_a2, 6);
    return var_s0;
}
