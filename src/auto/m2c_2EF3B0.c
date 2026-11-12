#include "m2c_macros.h"

M2C_UNK func_002F5CE8();                            /* extern */
M2C_UNK func_0030A5F0();                            /* extern */
extern s32 D_0034BC78 __attribute__((section(".data")));

s32 func_002EF3B0(void) {
    if (D_0034BC78 == 0) {
        D_0034BC78 = 1;
        func_002F5CE8();
        func_0030A5F0();
        D_0034BC78 = 0;
    }
    return 0;
}
