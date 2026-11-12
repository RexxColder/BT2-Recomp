#include "m2c_macros.h"

M2C_UNK func_0014E250(s32, M2C_UNK);                /* extern */
M2C_UNK func_0014E968(s32);                         /* extern */

void func_0016B288(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_0014E968(temp_s0);
    func_0014E250(temp_s0 + 0x1E80, 1);
}
