#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B6EF0(s32, s32, M2C_UNK, M2C_UNK);  /* extern */
s32 func_002B8280();                                /* extern */
extern M2C_UNK D_00378B68 __attribute__((section(".data")));
extern M2C_UNK D_00378B98 __attribute__((section(".data")));

void func_002B6E68(s32 arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378B68);
        return;
    }
    if (arg1 == 0) {
        Rand_Range(&D_00378B98);
        return;
    }
    func_002B6EF0(arg0, arg1, 0, -1);
}
