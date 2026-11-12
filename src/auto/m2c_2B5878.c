#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *, M2C_UNK);             /* extern */
M2C_UNK func_002B5138(s32, M2C_UNK);                /* extern */
s32 func_002B7CB8(s32);                             /* extern */
s32 func_002B8280();                                /* extern */
M2C_UNK func_002CEF30(s32, M2C_UNK);                /* extern */
extern M2C_UNK D_00378528 __attribute__((section(".data")));

void func_002B5878(s32 arg0, M2C_UNK arg1) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378528, 2);
        return;
    }
    func_002B5138(arg0, 2);
    func_002CEF30(func_002B7CB8(arg0), arg1);
}
