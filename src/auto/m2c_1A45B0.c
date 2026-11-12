#include "m2c_macros.h"

s32 BtlScene_IsEffectStopped(s32, u8);              /* extern */
M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001A41D0(s32, void *, void *);         /* extern */
M2C_UNK func_001A43C8(void *, void *);              /* extern */

void func_001A45B0(void *arg0) {
    s32 temp_s0;
    void *temp_s1;
    void *temp_s2;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    temp_s2 = temp_s1 + 0x10;
    temp_s0 = M2C_FIELD(temp_s2, s32 *, 0x38);
    if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s1, s32 *, 0x10), M2C_FIELD(temp_s1, u8 *, 0x54)) == 0) {
        func_001A41D0(temp_s0, temp_s1, temp_s2);
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x50) & 4) {
        BtlTask_SetDead(arg0);
        return;
    }
    func_001A43C8(temp_s1, temp_s2);
}
