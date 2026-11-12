#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001A5AF8(s32);                         /* extern */
M2C_UNK func_001A5DB0(s32);                         /* extern */

void func_001A5A00(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    func_001A5AF8(temp_s0);
    func_001A5DB0(temp_s0);
    BtlTask_SetDead(arg0);
}
