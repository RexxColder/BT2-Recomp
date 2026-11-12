#include "m2c_macros.h"

M2C_UNK func_003126C8();                /* extern */

// Calls func_003126C8 on three sub-blocks of arg0 (+0x950 alone, +0x960 with arg2, +0x970 with arg3).
void func_00211898(s32 arg0, s32 unused1, M2C_UNK arg2, M2C_UNK arg3) {
    func_003126C8(arg0 + 0x950, unused1);
    func_003126C8(arg0 + 0x960, arg2);
    func_003126C8(arg0 + 0x970, arg3);
}
