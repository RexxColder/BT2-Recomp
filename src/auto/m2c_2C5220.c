#include "m2c_macros.h"

M2C_UNK func_002C2FF0(void *, M2C_UNK);             /* extern */
s32 func_002C5270(s32);                             /* extern */

void func_002C5220(void *arg0) {
    if (func_002C5270(*M2C_FIELD(arg0, s32 **, 0x1F7C)) != 0) {
        func_002C2FF0(arg0, 0xFF000D0A);
    }
}
