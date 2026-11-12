#include "m2c_macros.h"

M2C_UNK func_002F8D60(s32, s32, s32);               /* extern */
M2C_UNK func_002F8DB0(s32, s16, s16, s16);          /* extern */

void func_002E7C48(void *arg0) {
    func_002F8D60(M2C_FIELD(arg0, s32 *, 8), arg0 + 0xAC, arg0 + 0xB0);
    func_002F8DB0(M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(arg0, s16 *, 0xA6), M2C_FIELD(arg0, s16 *, 0xA8), M2C_FIELD(arg0, s16 *, 0xAA));
}
