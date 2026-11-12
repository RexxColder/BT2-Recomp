#include "m2c_macros.h"

s32 func_002F14E0(s32);                             /* extern */
M2C_UNK func_002F4F88(void *, M2C_UNK, s16);        /* extern */

void func_002F7A18(void *arg0) {
    if (func_002F14E0(M2C_FIELD(arg0, s32 *, 4)) == 1) {
        func_002F4F88(arg0, 0, M2C_FIELD(arg0, s16 *, 0x42));
        return;
    }
    func_002F4F88(arg0, 0, M2C_FIELD(arg0, s16 *, 0x42));
    func_002F4F88(arg0, 1, M2C_FIELD(arg0, s16 *, 0x44));
}
