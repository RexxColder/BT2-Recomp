#include "m2c_macros.h"

s32 BtlScene_IsEffectStopped(s32, u8);              /* extern */
M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001932D0(void *, void *);              /* extern */
M2C_UNK func_001947D8(void *, void *);              /* extern */

void func_00194948(void *arg0) {
    void *temp_s0;
    void *temp_s1;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s1 = temp_s0 + 0x10;
    if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s1, s32 *, 0x40), M2C_FIELD(temp_s0, u8 *, 0x64)) == 0) {
        func_001932D0(temp_s0, temp_s1);
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x60) & 4) {
        BtlTask_SetDead(arg0);
        return;
    }
    func_001947D8(temp_s0, temp_s1);
}
