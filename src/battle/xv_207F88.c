#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);

/* returns (view->+0x958)->+0x38 of the object view for arg0, or 0 when either pointer is null */
s32 BtlCharApi_ObjGetParamFlags0(s32 arg0) {
    u8 *view = (u8 *)BtlObjVis_GetView_207EA0(arg0);
    if (view != NULL) {
        u8 *p = *(u8 **)(view + 0x958);
        if (p != NULL) {
            return *(s32 *)(p + 0x38);
        }
        return 0;
    }
    return (s32)view;
}
