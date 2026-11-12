#include "m2c_macros.h"

/* Stores arg2 at +0x1318 of the arg1-th 0x74-byte entry of the table at arg0, unless arg1 == 8. */
void func_002C0E10(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp;

    if (arg1 != 8) {
        temp = arg1 * 0x74;
        M2C_FIELD(arg0 + temp, s32 *, 0x1318) = arg2;
    }
}
