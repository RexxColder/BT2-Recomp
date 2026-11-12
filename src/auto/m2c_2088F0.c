#include "m2c_macros.h"

s32 BtlChar_GetPos(s32);                            /* extern */
s32 BtlObjVis_GetView_207EA0(u32, u32);             /* extern */
s32 func_00211288(u32);                             /* extern */
M2C_UNK func_003126C8(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));
extern s32 D_00387930;

void func_002088F0(u32 arg0, M2C_UNK arg1) {
    s32 temp_v0;

    if ((D_00387930 != 0) && (arg0 < 2U)) {
        func_003126C8(arg1, BtlChar_GetPos(func_00211288(arg0)) + 0x10);
        return;
    }
    temp_v0 = BtlObjVis_GetView_207EA0(arg0, arg0);
    if (temp_v0 != 0) {
        func_003126C8(arg1, temp_v0 + 0x9B0);
        return;
    }
    func_003126C8(arg1, &D_002C3630);
}
