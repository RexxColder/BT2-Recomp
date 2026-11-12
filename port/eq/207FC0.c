#include "common.h"

u8 *BtlObjVis_GetView_207EA0(s32 arg0);

s32  BtlCharApi_GetAuraType(s32 arg0) {
    u8 *v = BtlObjVis_GetView_207EA0(arg0);
    u8 *t;

    if (v == NULL) {
        return (s8)(0);
    }
    if (*(s32 *)(v + 0xAF0) & 0x40000) {
        return (s8)(3);
    }
    t = *(u8 **)(v + 0x958);
    if (t == NULL) {
        return (s8)(0);
    }
    return (s8)(*(s8 *)(t + 0x3F));
}
