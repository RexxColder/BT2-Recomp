#include "m2c_macros.h"

s32 func_002DCA68();                /* extern */
M2C_UNK func_002DCB88();       /* extern */
s32 func_002DCC38();                                /* extern */
extern s32 D_00347600 __attribute__((section(".data")));

/* Null-checked dispatcher: arg0 == 0 reports via D_00347600; otherwise a flag test picks a tail call or a callback. */
s32 func_002DCAF0(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (arg0 == 0) {
        func_002DCB88(D_00347600, arg1, arg2);
    } else if (func_002DCC38() != 0) {
        return func_002DCA68(0, 0xFF020101);
    } else {
        func_002DCB88(arg0 + 4, arg1, arg2);
    }
    return 0;
}
