#include "common.h"

u8 *func_00101A88(s32 arg0);

void func_00101EA8(s32 arg0, s32 arg1, s32 arg2) {
    u8 *temp_v0;
    s32 var_a1;
    u8 *var_v1;

    temp_v0 = func_00101A88(arg0);
    *(s8 *)(temp_v0 + 0x1C5) = (s8)((arg1 & 0xFF) != 1);
    var_a1 = 0;
    if (*(s32 *)temp_v0 > 0) {
        var_v1 = temp_v0 + 0x10;
        do {
            *(s32 *)var_v1 = arg2;
            var_a1 += 1;
            var_v1 += 0x58;
        } while (var_a1 < *(s32 *)temp_v0);
    }
}
