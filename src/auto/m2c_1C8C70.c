#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001C9278();                            /* extern */
M2C_UNK func_001C92E8(void *, s32);                 /* extern */

void func_001C8C70(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    func_001C9278(arg0);
    func_001C92E8(arg0, M2C_FIELD(temp_s1, s32 *, 0x90));
    BtlTask_SetDead(arg0);
}
