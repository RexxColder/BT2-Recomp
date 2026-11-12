#include "common.h"

/* 0x0020C9B0: view = BtlObjVis_GetView_207EA0(a0); if (view) func_00265AC8(view, a1 ? 1 : 7). */
s32 BtlObjVis_GetView_207EA0(s32 arg0);
void func_00265AC8(s32 arg0, s32 arg1);

void func_0020C9B0(s32 a0, s32 a1) {
    s32 view;
    s32 mode;

    mode = ((a1 & 0xFF) == 0) ? 7 : 1;
    view = BtlObjVis_GetView_207EA0(a0);
    if (view != 0) {
        func_00265AC8(view, mode);
    }
}
