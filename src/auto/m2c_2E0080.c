#include "m2c_macros.h"

extern s32 D_00399DEC __attribute__((section(".data")));

s32 func_002E0080(s32 arg0) {
    s32 var_a0;

    var_a0 = arg0;
    if (D_00399DEC != 0) {
        var_a0 |= 0x02000000;
    }
    return var_a0;
}
