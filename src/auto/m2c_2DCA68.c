#include "m2c_macros.h"

M2C_UNK func_002DCAB8(s32);                         /* extern */
extern s32 D_00347600 __attribute__((section(".data")));

s32 func_002DCA68(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        func_002DCAB8(D_00347600);
    } else {
        func_002DCAB8(arg0 + 4);
    }
    return arg1;
}
