#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);

/* 1 when the object's +0xAF0 flag word has bit 1 clear, 0 when set; 0 when there is no view */
s32 BtlCharApi_IsHidden(s32 arg0) {
    s32 *view = (s32 *)BtlObjVis_GetView_207EA0(arg0);
    if (view != NULL) {
        return (((*(s32 *)((u8 *)view + 0xAF0)) >> 1) ^ 1) & 1;
    }
    return (s32)view;
}
