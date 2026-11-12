#include "common.h"

u8 *BtlObjVis_GetView_207EA0(s32 arg0);

u8 *func_00208700(s32 arg0) {
    u8 *v = BtlObjVis_GetView_207EA0(arg0);
    u8 *t;

    if (v != NULL) {
        t = *(u8 **)(v + 0x958);
        v = NULL;
        if (t != NULL) {
            v = *(u8 **)(t + 0x68);
        }
    }
    return v;
}
