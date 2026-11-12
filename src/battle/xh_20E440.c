#include "m2c_macros.h"

s32 BtlChar_GetPos();                               /* extern */
M2C_UNK func_00312638(s32, s32, M2C_UNK);           /* extern */

// Calls func_00312638 on BtlChar_GetPos()+0xA0 (dst and src) with arg.
void func_0020E440(s32 unused0, M2C_UNK arg1) {
    s32 temp_v0;

    temp_v0 = BtlChar_GetPos(unused0) + 0xA0;
    func_00312638(temp_v0, temp_v0, arg1);
}
