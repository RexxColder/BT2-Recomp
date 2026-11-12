#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_0023F410(s32 arg0);
extern s32 D_00387930;

s32 func_0020AD28(u32 arg0) {
    s32 t;

    if (D_00387930 == 0 || arg0 >= 2U) {
        return 0;
    }
    t = func_00211288((s32)arg0);
    if (func_0023F410(t) & 0x10) {
        return 0;
    }
    return BtlObjXf_Update(t) == 0x42;
}
