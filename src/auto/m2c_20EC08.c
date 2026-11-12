#include "m2c_macros.h"

s32 BtlCtrl_IsInterruptible();                      /* extern */
s32 func_00211288(s32);                             /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_0020EC08(s32 arg0) {
    if (BtlCtrl_IsInterruptible(arg0) != 0) {
        func_002113C0(func_00211288(arg0), 7, 0x2000, 1);
    }
}
