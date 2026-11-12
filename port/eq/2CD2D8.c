#include "common.h"

s32 func_002C0690();
s32 func_002C06B0();
void func_002CF9B8(u8 *arg0, s32 arg1, s32 arg2);

void func_002CD2D8(u8 *arg0) {
    s32 var_a2;
    u8 *temp_s0;

    temp_s0 = arg0 + 0xA0C;
    if ((*(s32 *)(temp_s0 + 0x14) == 1) && (func_002C06B0(arg0, 1) == 0) && (func_002C0690(arg0, 1) == 0)) {
        *(s32 *)(temp_s0 + 0x14) = 0;
    }
    var_a2 = *(s32 *)(temp_s0 + 0x18);
    if (var_a2 == 1) {
        if (func_002C06B0(arg0, 2, var_a2) != 0) {
            var_a2 = *(s32 *)(temp_s0 + 0x18);
        } else if (func_002C0690(arg0, 2) != 0) {
            var_a2 = *(s32 *)(temp_s0 + 0x18);
        } else {
            *(s32 *)(temp_s0 + 0x18) = 0;
            var_a2 = 0;
        }
    }
    func_002CF9B8(arg0, *(s32 *)(temp_s0 + 0x14), var_a2);
}
