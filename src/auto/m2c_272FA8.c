#include "m2c_macros.h"

s32 BtlStage_IsReady();                             /* extern */
extern f32 D_00387EA0;
extern void *gBtlStage;

f32 func_00272FA8(void) {
    f32 *temp_v1;

    if (BtlStage_IsReady() == 0) {
        return D_00387EA0;
    }
    temp_v1 = M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(gBtlStage, s32 *, 0x40) * 4);
    D_00387EA0 = *temp_v1;
    return *temp_v1 - 100.0f;
}
