#include "m2c_macros.h"

M2C_UNK BtlTask_CreateChildList(void *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00148000(M2C_UNK);                     /* extern */
M2C_UNK func_0014E258(M2C_UNK, s32);                /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */

void func_00153FF8(void *arg0, M2C_UNK arg1) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x38);
    func_00148000(0x1E80);
    memset(temp_s1, 0, 0x1E80);
    func_0014E258(arg1, temp_s1);
    BtlTask_CreateChildList(arg0, 2, 0xAD0);
}
