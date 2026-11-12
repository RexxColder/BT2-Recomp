#include "m2c_macros.h"

M2C_UNK func_002E93C0();                            /* extern */
M2C_UNK func_002E93D8();                            /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */

void func_00307EA8(s32 arg0) {
    if (arg0 != 0) {
        func_002E93C0(arg0);
        memset(arg0, 0, 0x30);
        func_002E93D8();
    }
}
