#include "common.h"

void func_001B0798(void *arg0, s32 arg1) {
    u8 *var_a0;

    var_a0 = (u8 *)arg0;
    if (var_a0 != NULL) {
        do {
            *((u8 *)arg1 + *(s32 *)(*(u8 **)(var_a0 + 0x38) + 0x40)) = 1;
            var_a0 = *(u8 **)(var_a0 + 0x30);
        } while (var_a0 != NULL);
    }
}
