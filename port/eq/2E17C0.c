#include "common.h"

extern u8 D_0039D650[] __attribute__((section(".data")));

u8 *func_002E17C0(void) {
    s32 var_a2;
    s32 count;
    u8 *var_a0;
    u8 *var_v0;

    var_a2 = 0;
    count = *(s32 *)(D_0039D650 + 0x40);
    var_a0 = (u8 *)*(s32 *)(D_0039D650 + 0x44);
    if (count > 0) {
        do {
            var_v0 = var_a0;
            var_a0 += 0x640;
            if (*(s32 *)var_v0 == 1) {
                return var_v0;
            }
            var_a2 += 1;
        } while (var_a2 < count);
    }
    return NULL;
}
