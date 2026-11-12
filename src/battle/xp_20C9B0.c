#include "m2c_macros.h"

s32 BtlObjVis_GetView_207EA0();                     /* extern */
M2C_UNK func_00265AC8(s32, M2C_UNK);                /* extern */

void func_0020C9B0(s32 unused0, s32 arg1) {
    s32 temp_v0;
    s32 var_s0;

    var_s0 = arg1 & 0xFF;
    temp_v0 = BtlObjVis_GetView_207EA0(unused0);
    if (temp_v0 != 0) {
        func_00265AC8(temp_v0, (var_s0 != 0) ? 1 : 7);
    }
}
