#include "m2c_macros.h"

M2C_UNK func_001AEE98();                            /* extern */
M2C_UNK func_001E7070(s32);                         /* extern */

void func_001AEA68(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_001AEE98(arg0);
    func_001E7070(temp_s0 + 0x170);
}
