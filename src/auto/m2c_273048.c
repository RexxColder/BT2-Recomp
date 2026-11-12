#include "m2c_macros.h"

s32 BtlStage_IsReady();                             /* extern */
extern f32 D_00387EA8;
extern void *gBtlStage;

f32 func_00273048(void) {
    void *temp_v1;

    if (BtlStage_IsReady() == 0) {
        return D_00387EA8;
    }
    temp_v1 = M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(gBtlStage, s32 *, 0x40) * 4);
    D_00387EA8 = M2C_FIELD(temp_v1, f32 *, 8);
    return M2C_FIELD(temp_v1, f32 *, 8);
}
