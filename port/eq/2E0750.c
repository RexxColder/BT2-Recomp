#include "common.h"

extern void *D_00399E04 __attribute__((section(".data")));

s32 func_002E0750(u8 *arg0) {
    s32 var_v0;

    D_00399E04 = arg0;
    var_v0 = -1;
    if (arg0 != NULL) {
        var_v0 = ((*(s32 *)(arg0 + 0x188) ^ 2) == 0) ? 0 : -1;
    }
    return var_v0;
}
