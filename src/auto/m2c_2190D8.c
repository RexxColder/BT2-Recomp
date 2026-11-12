#include "m2c_macros.h"

s32 BtlObjXf_Update();                              /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_002190D8(s32 arg0) {
    if (BtlObjXf_Update(arg0) == 0x4C) {
        func_002113C0(arg0, 5, 0x200, 0);
    }
}
