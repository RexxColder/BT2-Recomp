#include "m2c_macros.h"

M2C_UNK func_00261B40();                            /* extern */
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002610D0(void) {
    if (!(D_003B2654 & 0x100)) {
        func_00261B40();
    }
}
