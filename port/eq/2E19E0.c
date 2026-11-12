#include "common.h"

extern u8 D_0039D650[] __attribute__((section(".data")));

void func_002E19E0(s32 arg0, s32 arg1) {
    s32 var_a2;
    u8 *var_v1;
    u8 *var_a0;

    var_a2 = *(s32 *)(D_0039D650 + 0x40);
    var_v1 = *(u8 **)(D_0039D650 + 0x44);
    if (var_a2 > 0) {
        var_a0 = var_v1 + arg0 * 4 + 0x18;
        do {
            if (*(s32 *)var_v1 == 2) {
                *(s32 *)var_a0 = arg1;
            }
            var_v1 += 0x640;
            var_a2 -= 1;
            var_a0 += 0x640;
        } while (var_a2 != 0);
    }
}
