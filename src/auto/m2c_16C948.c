#include "m2c_macros.h"

M2C_UNK BtlTask_CreateChildList(void *, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK func_00148000(M2C_UNK);                     /* extern */
M2C_UNK func_0014E258(void *, void *);              /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_0016C948(void *arg0, void *arg1) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    func_00148000(0x1E88);
    memset(temp_s1, 0, 0x1E88);
    if (M2C_FIELD(M2C_FIELD(arg1, void **, 0x20), s32 *, 0x30) & 0x4000) {
        M2C_FIELD(temp_s1, s8 *, 0x1E80) = 1;
        func_0014E258(arg1, temp_s1);
    }
    BtlTask_CreateChildList(arg0, 2, 0xD40);
}
