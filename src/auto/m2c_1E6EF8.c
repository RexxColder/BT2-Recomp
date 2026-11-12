#include "m2c_macros.h"

s32 BtlScene_IsEffectStopped(u32, u8);              /* extern */
M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK func_001E6A50(void *);                      /* extern */
M2C_UNK func_001E6AD0(void *);                      /* extern */

void func_001E6EF8(void *arg0) {
    void *temp_s0;
    void *temp_s1;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    temp_s1 = temp_s0 + 0xC;
    if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s1, u32 *, 0x14), M2C_FIELD(temp_s0, u8 *, 4)) == 0) {
        if ((u32) M2C_FIELD(temp_s1, u32 *, 0x14) < 2U) {
            func_001E6A50(temp_s0);
        } else {
            func_001E6A50(temp_s0);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0) & 8) {
        BtlTask_SetDead(arg0);
        return;
    }
    func_001E6AD0(temp_s0);
}
