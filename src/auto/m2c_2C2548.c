#include "m2c_macros.h"

M2C_UNK func_002C2588(s32, s32);                    /* extern */
s32 func_002C26C0();                                /* extern */

void func_002C2548(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_002C26C0(arg0);
    if (temp_v0 != 0) {
        func_002C2588(temp_v0, arg0 + 0x78);
    }
}
