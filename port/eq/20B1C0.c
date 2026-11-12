#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);

void *func_0020B1C0(s32 arg0) {
    void *v;
    u8 *a;

    v = BtlObjVis_GetView_207EA0(arg0);
    if (v == NULL) {
        return NULL;
    }
    a = *(u8 **)((u8 *)v + 0x958);
    if (a == NULL) {
        return NULL;
    }
    if (!(*(s32 *)(a + 0x30) & 0x40)) {
        return NULL;
    }
    if ((*(s64 *)((u8 *)v + 0xAF0) & 0x22) == 0x22) {
        return (void *)1;
    }
    return NULL;
}
