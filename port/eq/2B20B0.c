#include "common.h"

s32 func_002B1DD0(s32 arg0);

extern s32 D_00387E18;

s32 func_002B20B0(void) {
    s32 var_v0;

    var_v0 = -1;
    if (D_00387E18 != 0) {
        var_v0 = *(s32 *) ((u8 *) func_002B1DD0(0) + 0x1C);
    }
    return var_v0;
}
