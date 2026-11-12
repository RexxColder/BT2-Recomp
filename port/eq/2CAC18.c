#include "common.h"

void func_002C32B0(s32 arg0);
void func_002C32C8(s32 arg0);

s32 func_002CAC18(u8 *arg0) {
    s32 sp[4];
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a1;
    s32 var_s0;
    u8 *temp_a2;
    u8 *var_a0;

    func_002C32B0((s32)sp);
    temp_a2 = *(u8 **)(arg0 + 0x1FC0);
    var_s0 = 0;
    temp_v0 = *(s32 *)(temp_a2 + 0x178);
    var_a0 = temp_a2 + 0x180;
    if (temp_v0 > 0) {
        var_a1 = temp_v0;
        do {
            temp_v0_2 = *(s32 *)var_a0;
            if ((temp_v0_2 == 2) || (temp_v0_2 == 4)) {
                var_s0 = ((*(s32 *)(var_a0 + 0x58) ^ -1) == 0) ? (var_s0 + 1) : var_s0;
            }
            var_a1 -= 1;
            var_a0 += 0xF0;
        } while (var_a1 != 0);
    }
    if (*(s32 *)(temp_a2 + 0x7C) == 1) {
        var_s0 = (var_s0 == 0) ? -1 : var_s0;
    }
    func_002C32C8((s32)sp);
    return var_s0;
}
