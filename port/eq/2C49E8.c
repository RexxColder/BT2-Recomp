#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1);
void func_002C4720(s32 arg0, s32 arg1);

void func_002C49E8(s32 arg0, s32 *arg1) {
    s32 var_a1;
    u8 *temp_s1;
    u8 *temp_v0;

    temp_v0 = (u8 *)arg0 + 0x1F74;
    temp_s1 = *(u8 **)(temp_v0 + 8);
    var_a1 = 0;
    if (func_002C0EA8(arg0, *(s32 *)(temp_v0 + 0x10)) == 1) {
        func_002C4720(arg0, *(s32 *)(temp_s1 + 0x3C));
        var_a1 = 1;
    }
    if (arg1 != NULL) {
        *arg1 = var_a1;
    }
}
