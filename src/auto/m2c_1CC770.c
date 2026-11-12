#include "m2c_macros.h"

s32 BtlScene_IsEffectStopped(s32, u8);              /* extern */
M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK EftMod1CC_BuildTex(void *, void *);         /* extern */
f32 func_001CB6E8(s32);                      /* extern */

void EftMod1CC_Update(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s0, s32 *, 0), M2C_FIELD(temp_s0, u8 *, 0x44)) == 0) {
        func_001CB6E8(temp_s0);
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x40) & 4) {
        BtlTask_SetDead(arg0);
        return;
    }
    EftMod1CC_BuildTex(temp_s0, temp_s0);
}
