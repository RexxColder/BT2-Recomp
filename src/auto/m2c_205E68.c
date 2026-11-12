#include "m2c_macros.h"

M2C_UNK func_002113C0(void *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
s32 func_0025FBE8(s32, M2C_UNK);                    /* extern */

void func_00205E68(void *arg0) {
    if (func_0025FBE8(M2C_FIELD(arg0, s32 *, 0x1530), 0x02000000) != 0) {
        func_002113C0(arg0, 9, 0x100000, 1);
    }
    if (func_0025FBE8(M2C_FIELD(arg0, s32 *, 0x1530), 0x04000000) != 0) {
        func_002113C0(arg0, 9, 0x100000, 0);
    }
}
