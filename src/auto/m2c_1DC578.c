#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001DCE58();                            /* extern */
M2C_UNK func_001DCED8(void *, s32);                 /* extern */

void func_001DC578(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    func_001DCE58(arg0);
    func_001DCED8(arg0, M2C_FIELD(temp_s1, s32 *, 0x244));
    BtlTask_SetDead(arg0);
}
