#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);

/* same as func_00208738 with the word at +0x960 */
s32 func_00208768(s32 arg0, s32 arg1) {
    return *(s32 *)((u8 *)BtlObjVis_GetView_207EA0(arg0) + arg1 * 4 + 0x960);
}
