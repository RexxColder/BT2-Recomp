#include "m2c_macros.h"

M2C_UNK func_002F5CE8();                            /* extern */
extern s32 D_0034AED8 __attribute__((section(".data")));

void func_002ED198(void) {
    D_0034AED8 += 1;
    func_002F5CE8();
}
