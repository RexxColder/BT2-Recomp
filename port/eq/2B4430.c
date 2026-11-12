#include "common.h"

void func_002B4430(u8 *arg0, u8 *arg1) {
    u8 *var_a3;
    s32 var_t0;

    *(s32 *)(arg0 + 0x1EC) = *(s32 *)(arg1 + 0x18);
    var_t0 = 0x1F;
    *(s32 *)(arg0 + 0x1F0) = *(s32 *)(arg1 + 0x1C);
    *(s32 *)(arg0 + 0x1F8) = 0;
    *(s32 *)(arg0 + 0x1F4) = *(s32 *)(arg1 + 0x18);
    *(s32 *)(arg0 + 0x200) = 0;
    var_a3 = arg0 + 0x280;
    do {
        var_t0 -= 1;
        *(s32 *)var_a3 = 0;
        var_a3 -= 4;
    } while (var_t0 >= 0);
}
