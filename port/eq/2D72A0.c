#include "common.h"

extern u8 D_00347368[] __attribute__((section(".data")));

u8 *func_002D72A0(void) {
    s32 var_a2;
    s32 count;
    u8 *var_a0;
    u8 *var_v0;

    var_a2 = 0;
    count = *(s32 *)(D_00347368 + 8);
    if (count > 0) {
        var_a0 = D_00347368 + 0xC;
        do {
            var_v0 = var_a0;
            var_a0 += 0x4C;
            if (*(s32 *)var_v0 == 0) {
                return var_v0;
            }
            var_a2 += 1;
        } while (var_a2 < count);
    }
    return NULL;
}
