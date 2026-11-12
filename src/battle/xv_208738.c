#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);

/* returns the view word at +0x940 of entry arg1 of the table returned by BtlObjVis_GetView_207EA0(arg0) */
s32 func_00208738(s32 arg0, s32 arg1) {
    return *(s32 *)((u8 *)BtlObjVis_GetView_207EA0(arg0) + arg1 * 4 + 0x940);
}
