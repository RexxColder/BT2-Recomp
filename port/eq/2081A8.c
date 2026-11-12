#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
extern u8 D_0036F990[12] __attribute__((section(".data")));

/* 0x002081A8(): copies the 12 bytes at D_0036F990 to a table. view = BtlObjVis_GetView_207EA0(arg0); when view is NULL or
 * view->+0x958 is 0 the result is 0. Otherwise r = BtlChar_FrameMod(6) and the result is tab[2r] * 9 + tab[2r + 1]. */
s32 func_002081A8(s32 arg0) {
    u8 tab[12];
    s32 view;
    s32 r;
    s32 k;

    for (k = 0; k < 12; k++) {
        tab[k] = D_0036F990[k];
    }
    view = BtlObjVis_GetView_207EA0(arg0);
    if (view == 0) {
        return 0;
    }
    if (*(s32 *)(view + 0x958) == 0) {
        return 0;
    }
    r = BtlChar_FrameMod(6);
    return tab[2 * r] * 9 + tab[2 * r + 1];
}
