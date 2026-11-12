#include "m2c_macros.h"

s32 BtlScene_IsEffectStopped(s32, s32);             /* extern */
M2C_UNK BtlTask_SetDead(void *);                    /* extern */
M2C_UNK GfxLens_SetHold(s32, M2C_UNK);              /* extern */
M2C_UNK GfxLens_SetPos(s32, void *);                /* extern */

void func_001B5400(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x38);
    if (M2C_FIELD(temp_s0, s32 *, 0x50) != -1) {
        if (BtlScene_IsEffectStopped(M2C_FIELD(temp_s0, s32 *, 0x2C), M2C_FIELD(temp_s0, s32 *, 0x30)) != 0) {
            GfxLens_SetHold(M2C_FIELD(temp_s0, s32 *, 0x50), 1);
            return;
        }
        GfxLens_SetHold(M2C_FIELD(temp_s0, s32 *, 0x50), 0);
        GfxLens_SetPos(M2C_FIELD(temp_s0, s32 *, 0x50), temp_s0 + 0x40);
        if (M2C_FIELD(temp_s0, s32 *, 0x54) & 1) {
            BtlTask_SetDead(arg0);
        }
    }
}
