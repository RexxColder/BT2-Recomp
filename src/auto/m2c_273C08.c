#include "m2c_macros.h"

M2C_UNK func_003126C8(M2C_UNK, s32);                /* extern */
extern void *gBtlStage;

void func_00273C08(void *arg0, M2C_UNK arg1) {
    func_003126C8(arg1, M2C_FIELD(gBtlStage, s32 *, 0x5C) + (M2C_FIELD(arg0, s32 *, 8) * 4) + 0x30);
}
