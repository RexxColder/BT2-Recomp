#include "m2c_macros.h"

M2C_UNK func_001C7C38(s32);                         /* extern */
M2C_UNK func_001C7DF0();                            /* extern */

void func_001C7878(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_001C7DF0(arg0);
    func_001C7C38(temp_s0);
}
