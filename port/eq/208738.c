#include "common.h"

/* 0x00208738: v = BtlObjVis_GetView_207EA0(a0); return *(s32 *)(v + (a1 << 2) + 0x940). */
s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00208738(s32 a0, s32 a1) {
    u8 *v;

    v = (u8 *)BtlObjVis_GetView_207EA0(a0);
    return *(s32 *)(v + (a1 << 2) + 0x940);
}
