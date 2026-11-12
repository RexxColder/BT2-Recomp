#include "m2c_macros.h"

s32 func_002ADFD8();                                /* extern */
M2C_UNK func_002AF578(s32, M2C_UNK);                /* extern */
M2C_UNK func_002B1CA8(s32, M2C_UNK);                /* extern */
M2C_UNK func_002B1F08(s32);                         /* extern */

void func_002AEC78(s32 arg0) {
    if (func_002ADFD8(arg0) != 0) {
        func_002AF578(arg0, 0x26);
    } else {
        func_002AF578(arg0, 0x23);
    }
    func_002B1CA8(arg0, 8);
    func_002B1F08(arg0);
}
