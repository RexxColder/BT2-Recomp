#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_0019C170(void *, s32);                       /* extern */

void func_0019BAF0(void *arg0) {
    func_0019C170(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x80));
    BtlTask_SetDead(arg0);
}
