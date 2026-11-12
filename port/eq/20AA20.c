#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

s32 func_0020AA20(s32 arg0) {
    s32 temp_v0;

    if (D_00387930 == 0) {
        return 0;
    }
    if ((u32)arg0 >= 2U) {
        return 0;
    }
    temp_v0 = func_001FA3A8(BtlObjXf_Update(func_00211288(arg0)));
    if ((temp_v0 & 0x10) != 0) {
        return 1;
    }
    return 0;
}
