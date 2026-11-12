#include "common.h"

extern u8 D_00399DA8[] __attribute__((section(".data")));

u8 *func_002E03F8(void) {
    s32 var_a2;
    s32 count;
    u8 *var_a0;
    u8 *var_v0;

    var_a2 = 0;
    count = *(s32 *)(D_00399DA8 + 0x54);
    var_a0 = (u8 *)*(s32 *)(D_00399DA8 + 0x58);
    if (count > 0) {
        do {
            var_v0 = var_a0;
            var_a0 += 0x440;
            if (*(s32 *)(var_v0 + 0x188) == 1) {
                return var_v0;
            }
            var_a2 += 1;
        } while (var_a2 < count);
    }
    return NULL;
}
