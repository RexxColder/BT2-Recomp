#include "common.h"

extern s32 D_003877B8 __attribute__((section(".data")));

s32 func_0018E558(void *arg0) {
    s32 var_v0;
    u8 *temp_a0;

    var_v0 = 0;
    if ((D_003877B8 != 0) && (arg0 != NULL)) {
        temp_a0 = *(u8 **)((u8 *)arg0 + 0x38);
        if (temp_a0 != NULL) {
            var_v0 = (*(u16 *)(temp_a0 + 0x56) & 2) != 0;
        }
    }
    return var_v0;
}
