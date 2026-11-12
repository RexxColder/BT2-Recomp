#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B7088(s32, s32);                    /* extern */
M2C_UNK func_002B7590(s32, s32, M2C_UNK, M2C_UNK);  /* extern */
s32 func_002B8280();                                /* extern */
s32 func_002B8C98(s32);                             /* extern */
extern M2C_UNK D_00378DB0 __attribute__((section(".data")));
extern M2C_UNK D_00378DE8 __attribute__((section(".data")));

void func_002B76A8(s32 arg0, s32 arg1, M2C_UNK arg2, M2C_UNK arg3) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378DB0);
        return;
    }
    if (arg1 == 0) {
        Rand_Range(&D_00378DE8);
        return;
    }
    func_002B7088(arg0, func_002B8C98(arg0));
    func_002B7590(arg0, arg1, arg2, arg3);
}
