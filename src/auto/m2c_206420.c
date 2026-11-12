#include "m2c_macros.h"

M2C_UNK func_002667E8(s32);                         /* extern */

void BtlFx_SpawnFlashReq20(void *arg0) {
    if (M2C_FIELD(arg0, s64 *, 0x338) & 0x800000) {
        func_002667E8(M2C_FIELD(arg0, s32 *, 0x1530));
    }
}
