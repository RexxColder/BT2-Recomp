#include "common.h"

extern u8 D_003B2654[] __attribute__((section(".data")));

s32 func_002ABB40(void) {
    s32 temp_a0;
    s32 var_v0;
    u8 *temp_a2;

    temp_a2 = D_003B2654 + 0x5C;
    temp_a0 = *(s32 *)(temp_a2 + 0x24);
    var_v0 = 2;
    if (temp_a0 == 1) {
        if (*(s32 *)(D_003B2654 + 0x4) == *(s32 *)(temp_a2 + 0x2C)) {
            return 1;
        }
        return 0;
    }
    if (temp_a0 != 2 || *(s32 *)(D_003B2654 + 0x8) != *(s32 *)(temp_a2 + 0x2C)) {
        return 0;
    }
    return var_v0;
}
