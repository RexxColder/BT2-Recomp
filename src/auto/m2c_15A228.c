#include "m2c_macros.h"

s32 BtlScene_IsCharStopped(s32);                    /* extern */
M2C_UNK func_00129C38(void *, void *);              /* extern */

void func_0015A228(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    if (BtlScene_IsCharStopped(*M2C_FIELD(temp_s1, s32 **, 0xA0)) == 0) {
        if (M2C_FIELD(arg0, s32 *, 4) & 4) {
            func_00129C38(temp_s1 + 0x70, arg0 + 0x10);
        }
        if (!(M2C_FIELD(arg0, s32 *, 4) & 1)) {
            if (M2C_FIELD(arg0, s32 *, 4) & 2) {
                goto block_5;
            }
        } else {
block_5:
            M2C_FIELD(temp_s1, s32 *, 0) = (s32) (M2C_FIELD(temp_s1, s32 *, 0) & ~0x10);
        }
    }
}
