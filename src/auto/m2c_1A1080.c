#include "m2c_macros.h"

M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001A0CA8(s32, void *);                 /* extern */

void func_001A1080(void *arg0) {
    s32 temp_v0;
    void *temp_a0;

    temp_a0 = M2C_FIELD(arg0, void **, 0x38);
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0x40);
    if (!(temp_v0 & 4)) {
        M2C_FIELD(temp_a0, s32 *, 0x40) = (s32) (temp_v0 | 4);
        func_001A0CA8(M2C_FIELD(temp_a0, s32 *, 0), arg0);
    }
    BtlTask_SetDead(arg0);
}
