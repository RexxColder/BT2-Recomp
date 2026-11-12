#include "m2c_macros.h"

M2C_UNK func_002AC948(s32);                         /* extern */
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern M2C_UNK D_003B2600 __attribute__((section(".data")));

void func_002A89E8(s32 arg0) {
    s32 var_s0;

    var_s0 = arg0 & 0xFF;
    memset(&D_003B2600, 0, 0x634);
    func_002AC948(var_s0);
}
