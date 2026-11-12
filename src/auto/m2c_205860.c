#include "m2c_macros.h"

M2C_UNK func_001A5EF0();        /* extern */
M2C_UNK func_00208DE8();        /* extern */
M2C_UNK func_0020FC38();             /* extern */

void BtlChar_SpawnHitFx(void *arg0) {
    s32 sp[4];
    if (M2C_FIELD(arg0, s64 *, 0x338) & 0x08000000) {
        func_00208DE8(M2C_FIELD(arg0, s32 *, 0x1534), sp, 0x2E);
        func_001A5EF0(0xD, sp, M2C_FIELD(arg0, s32 *, 0x1534));
        func_0020FC38(arg0, 0xA);
    }
}
