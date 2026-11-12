#include "m2c_macros.h"

M2C_UNK func_002E7090();                            /* extern */
M2C_UNK func_002F8C40();                            /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00347BF8 __attribute__((section(".data")));

void func_002E7358(void) {
    func_002F8C40();
    func_002E7090();
    memset(&D_00347BF8, 0, 0x1040);
}
