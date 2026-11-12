#include "common.h"

extern u8 D_00347A30[] __attribute__((section(".data")));

u8 *func_002E0D78(void) {
    s32 var_a2;
    s32 count;
    u8 *var_a0;
    u8 *var_v0;

    var_a2 = 0;
    count = *(s32 *)(D_00347A30 + 4);
    if (count > 0) {
        var_a0 = D_00347A30 + 8;
        do {
            var_v0 = var_a0;
            var_a0 += 0x24;
            if (*(s32 *)var_v0 == 0) {
                return var_v0;
            }
            var_a2 += 1;
        } while (var_a2 < count);
    }
    return NULL;
}
