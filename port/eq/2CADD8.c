#include "common.h"

void func_002C32B0(s32 arg0, s32 arg1, s32 arg2);
void func_002C32C8(s32 arg0);
s32 func_002CB250(s32 arg0, s32 arg1);

u8 *func_002CADD8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s1;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s2;

    var_s2 = 0;
    func_002C32B0((s32)sp, arg1, arg2);
    temp_v0 = *(u8 **)((u8 *)arg0 + 0x1FC0);
    temp_v1 = *(s32 *)(temp_v0 + 0x178);
    var_s0 = temp_v0 + 0x180;
    if (temp_v1 > 0) {
        var_s1 = temp_v1;
        do {
            temp_v0_2 = *(s32 *)var_s0;
            if (((temp_v0_2 == 2) || (temp_v0_2 == 4)) && (*(s32 *)(var_s0 + 0x58) == -1)) {
                var_s2 = (func_002CB250((s32)var_s2, (s32)var_s0) != 0) ? var_s0 : var_s2;
            }
            var_s1 -= 1;
            var_s0 += 0xF0;
        } while (var_s1 != 0);
    }
    func_002C32C8((s32)sp);
    return var_s2;
}
