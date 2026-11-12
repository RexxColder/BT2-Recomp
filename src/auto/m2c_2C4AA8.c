#include "m2c_macros.h"

s32 func_002C0E40(void *, s32);                     /* extern */
s32 func_002C4B30();                                /* extern */
M2C_UNK func_002C4BC0(void *, M2C_UNK);             /* extern */
s32 func_002C4C60(void *, s32);                     /* extern */

void func_002C4AA8(void *arg0) {
    s32 temp_s0;

    if (func_002C4B30(arg0) != 1) {
        temp_s0 = M2C_FIELD(arg0, s32 *, 0x1F84);
        if ((func_002C0E40(arg0, temp_s0) == 1) && (func_002C4C60(arg0, temp_s0) != 0)) {
            func_002C4BC0(arg0, 1);
        }
    }
}
