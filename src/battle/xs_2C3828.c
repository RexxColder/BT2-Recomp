#include "m2c_macros.h"

void BtlObjAnim_PlayModel(void *arg0, s32 arg1, s32 arg2) {
    if (arg0 != NULL) {
        M2C_FIELD(arg0, s32 *, 0x37A0) = arg1;
        M2C_FIELD(arg0, s32 *, 0x37A4) = arg2;
    }
}
