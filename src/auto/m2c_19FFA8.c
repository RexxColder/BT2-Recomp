#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
s32 func_00126560();                                /* extern */
M2C_UNK func_001A0428(void *);                      /* extern */
M2C_UNK func_001A0870(void *);                      /* extern */

void func_0019FFA8(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    if (func_00126560() != 0) {
        func_001A0870(arg0);
    } else {
        func_001A0428(arg0);
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x28) & 0x20) {
        BtlTask_SetDead(arg0);
    }
}
