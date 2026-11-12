#include "m2c_macros.h"

M2C_UNK func_00284AC8();                            /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_00388F30 __attribute__((section(".data")));

void func_00284B18(void) {
    memset(&D_00388F30, 0, 0x120);
    func_00284AC8();
}
