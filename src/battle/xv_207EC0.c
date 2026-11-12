#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);

/* the word at +4 of the object view for arg0, or 0 when there is no view */
s32 func_00207EC0(s32 arg0) {
    u8 *view = (u8 *)BtlObjVis_GetView_207EA0(arg0);
    if (view != NULL) {
        return *(s32 *)(view + 4);
    }
    return (s32)view;
}
