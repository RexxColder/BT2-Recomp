#include "m2c_macros.h"

M2C_UNK func_003126C8(s32, s32);                    /* extern */

void Rigid_SyncSpheres(s32 arg0) {
    s32 temp_s1;

    temp_s1 = arg0 + 0x40;
    func_003126C8(arg0 + 0x1D0, temp_s1);
    func_003126C8(arg0 + 0x1F0, temp_s1);
}
