#include "m2c_macros.h"

s32 func_002B78D8();                                /* extern */
M2C_UNK func_002B7960(M2C_UNK);                     /* extern */
M2C_UNK func_002B7980(M2C_UNK, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK func_002B7A60(M2C_UNK *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_002B7B58(M2C_UNK);                     /* extern */
extern s32 D_00346BE8 __attribute__((section(".data")));
extern M2C_UNK D_0038BD40 __attribute__((section(".data")));
extern M2C_UNK D_0038FD40 __attribute__((section(".data")));

void func_002B7828(void) {
    if ((func_002B78D8() == 1) && (D_00346BE8 != 0)) {
        func_002B7960(1);
        func_002B7980(0, 0x4000, &D_0038FD40);
        func_002B7B58(8);
        func_002B7A60(&D_0038BD40, 0x4000, 0);
        func_002B7B58(9);
        D_00346BE8 = 0;
    }
}
