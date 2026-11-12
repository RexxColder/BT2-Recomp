#include "common.h"

extern u8 D_003553F0[] __attribute__((section(".data")));

void *func_002FCC10(u32 arg0) {
    void *var_v0;

    var_v0 = NULL;
    if (arg0 < 0x10U) {
        var_v0 = D_003553F0 + arg0 * 0x44;
    }
    return var_v0;
}
