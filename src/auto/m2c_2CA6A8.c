#include "m2c_macros.h"

M2C_UNK func_002C32B0();                      /* extern */
M2C_UNK func_002C32C8();                      /* extern */
s32 func_002CA708();           /* extern */

s32 func_002CA6A8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 sp[4];
    s32 temp_s0;

    func_002C32B0(sp, arg1, arg2);
    temp_s0 = func_002CA708(arg0, arg1, arg2);
    func_002C32C8(sp);
    return temp_s0;
}
