#include "m2c_macros.h"

s32 func_002ADFD8();                                /* extern */
M2C_UNK func_002AF578(s32, M2C_UNK);                /* extern */

void func_002AE2B0(s32 arg0) {
    if (func_002ADFD8(arg0) != 0) {
        func_002AF578(arg0, 0x26);
        return;
    }
    func_002AF578(arg0, 0x18);
}
