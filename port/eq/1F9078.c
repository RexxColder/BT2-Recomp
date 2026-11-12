#include "common.h"

void func_00207340(s32 arg0, s32 arg1);
s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
extern u8 *D_00387930;

void func_001F9078(void) {
    s32 temp_a1;
    s32 var_s0;
    u8 *temp_v0;

    *(s32 *)(D_00387930 + 8) = *(s32 *)(D_00387930 + 8) ^ 1;
    var_s0 = 0;
    if (*(s32 *)(D_00387930 + 8) & 1) {
        while (var_s0 < func_00211270()) {
            temp_v0 = func_00211288(var_s0);
            temp_a1 = var_s0 ^ 1;
            *(s32 *)(temp_v0 + 0x1534) = var_s0;
            var_s0 += 1;
            *(s32 *)(temp_v0 + 0x1538) = temp_a1;
            *(s32 *)(temp_v0 + 0x153C) = temp_a1;
            func_00207340((s32)temp_v0, temp_a1);
        }
        return;
    }
    while (var_s0 < func_00211270()) {
        temp_v0 = func_00211288(var_s0);
        temp_a1 = var_s0;
        *(s32 *)(temp_v0 + 0x1534) = var_s0;
        *(s32 *)(temp_v0 + 0x1538) = var_s0;
        *(s32 *)(temp_v0 + 0x153C) = var_s0;
        var_s0 += 1;
        func_00207340((s32)temp_v0, temp_a1);
    }
}
