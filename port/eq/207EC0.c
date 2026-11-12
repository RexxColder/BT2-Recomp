#include "common.h"

/* 0x00207EC0: v = BtlObjVis_GetView_207EA0(a0); return v ? *(s32 *)(v + 4) : v. */
s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00207EC0(s32 a0) {
    u8 *v;

    v = (u8 *)BtlObjVis_GetView_207EA0(a0);
    if (v != NULL) {
        return *(s32 *)(v + 4);
    }
    return (s32)v;
}
