#include "m2c_macros.h"

s32 BtlObjVis_GetView_207EA0();                     /* extern */
s32 func_00269A40(s32, M2C_UNK);                    /* extern */
M2C_UNK func_003126C8(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_002C3630 __attribute__((section(".data")));

// Same as func_00208E88 but uses entry at +0x90.
void func_00209080(s32 unused0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = BtlObjVis_GetView_207EA0(unused0);
    if (temp_v0 == 0) {
        func_003126C8(arg1, &D_002C3630);
        return;
    }
    temp_v0_2 = func_00269A40(temp_v0, arg2);
    if (temp_v0_2 == 0) {
        func_003126C8(arg1, &D_002C3630);
        return;
    }
    func_003126C8(arg1, (void *) (temp_v0_2 + 0x90));
}
