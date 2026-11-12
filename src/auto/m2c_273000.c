#include "m2c_macros.h"

s32 BtlStage_IsReady();                             /* extern */
extern f32 D_00387EA4;
extern void *gBtlStage;

f32 func_00273000(void) {
    void *temp_v1;

    if (BtlStage_IsReady() == 0) {
        return D_00387EA4;
    }
    temp_v1 = M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(gBtlStage, s32 *, 0x40) * 4);
    D_00387EA4 = M2C_FIELD(temp_v1, f32 *, 4);
    return M2C_FIELD(temp_v1, f32 *, 4);
}
