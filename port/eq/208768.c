#include "common.h"

u8 *BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00208768(s32 arg0, s32 arg1) {
    u8 *view = BtlObjVis_GetView_207EA0(arg0);

    return *(s32 *)(view + arg1 * 4 + 0x960);
}
