#include "m2c_macros.h"

s32 func_002B1DD0(M2C_UNK);                         /* extern */
s32 func_002B1DF8(s32);                             /* extern */
extern s32 D_00387E18;

s32 func_0020C918(void) {
    if (D_00387E18 != 0) {
        return func_002B1DF8(func_002B1DD0(0));
    }
    return -1;
}
