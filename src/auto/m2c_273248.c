#include "m2c_macros.h"

extern void *gBtlStage;

s32 func_00273248(s32 arg0) {
    return M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(gBtlStage, s32 *, 0x3C) * 4) + (arg0 << 6);
}
