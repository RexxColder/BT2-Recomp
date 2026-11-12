#include "common.h"

/* 0x00207F88: v = GetView(a0); if (!v) return 0; w = v->+0x958; if (!w) return 0; return w->+0x38. */
s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00207F88(s32 a0) {
    u8 *v;
    u8 *w;

    v = (u8 *)BtlObjVis_GetView_207EA0(a0);
    if (v == NULL) {
        return 0;
    }
    w = *(u8 **)(v + 0x958);
    if (w == NULL) {
        return 0;
    }
    return *(s32 *)(w + 0x38);
}
