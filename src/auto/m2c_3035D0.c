#include "m2c_macros.h"

M2C_UNK func_002EFAB8(M2C_UNK *);                   /* extern */
extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));
extern M2C_UNK D_0037F3D0 __attribute__((section(".data")));

void func_003035D0(void) {
    if ((D_0035D228 != 1) || (D_0035D220 > 0)) {
        func_002EFAB8(&D_0037F3D0);
    }
}
