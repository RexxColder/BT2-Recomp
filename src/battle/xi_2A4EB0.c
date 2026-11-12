#include "m2c_macros.h"

void *func_002A3DB8();                              /* extern */

// Stores the low byte of the second argument at +0x18 of the object returned by func_002A3DB8.
void func_002A4EB0(s32 arg0, s32 arg1) {
    u8 val = (u8) (arg1 & 0xFF);

    M2C_FIELD(func_002A3DB8(arg0), u8 *, 0x18) = val;
}
