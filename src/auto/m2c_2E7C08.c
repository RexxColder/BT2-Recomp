#include "m2c_macros.h"

M2C_UNK func_002F8D88(s32, s32, s32);               /* extern */
M2C_UNK func_002F8DC0(s32, void *, void *, void *); /* extern */

void func_002E7C08(void *arg0) {
    func_002F8D88(M2C_FIELD(arg0, s32 *, 8), arg0 + 0xAC, arg0 + 0xB0);
    func_002F8DC0(M2C_FIELD(arg0, s32 *, 8), arg0 + 0xA6, arg0 + 0xA8, arg0 + 0xAA);
}
