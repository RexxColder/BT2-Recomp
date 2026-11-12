#include "common.h"

/* 0x0020A508 (BtlCharApi_IsHidden in config): v = GetView(a0); if (!v) return 0;
   return ((*(s32 *)(v + 0xAF0) >> 1) ^ 1) & 1. */
s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_0020A508(s32 a0) {
    u8 *v;
    s32 t;

    v = (u8 *)BtlObjVis_GetView_207EA0(a0);
    if (v == NULL) {
        return 0;
    }
    t = *(s32 *)(v + 0xAF0);
    t = t >> 1;
    t = t ^ 1;
    return t & 1;
}
