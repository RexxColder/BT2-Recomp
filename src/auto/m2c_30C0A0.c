#include "m2c_macros.h"

M2C_UNK func_0030BF30();                            /* extern */
M2C_UNK func_0030BF48();                            /* extern */
s32 func_0030C0E8(s32, M2C_UNK);                    /* extern */

s32 func_0030C0A0(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_0030BF30(arg0, arg1);
    temp_s0 = func_0030C0E8(arg0, arg1);
    func_0030BF48();
    return temp_s0;
}
