#include "common.h"

/* 0x00209110: view = BtlObjVis_GetView_207EA0(a0); no view -> 0.0f; else b = func_00269A08(view, a1);
 * returns b ? *(f32 *)(b + 0x5C) : 1.0f. */
s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 func_00269A08(s32 arg0, s32 arg1);

f32 func_00209110(s32 a0, s32 a1) {
    s32 view;
    u8 *b;

    view = BtlObjVis_GetView_207EA0(a0);
    if (view == 0) {
        return 0.0f;
    }
    b = (u8 *)func_00269A08(view, a1);
    if (b != 0) {
        return *(f32 *)(b + 0x5C);
    }
    return 1.0f;
}
