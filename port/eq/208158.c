#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00208158(s32 arg0, s32 arg1) {
    s32 view = BtlObjVis_GetView_207EA0(arg0);
    s32 off;

    if (view == 0) {
        return 0;
    }
    off = *(s32 *)(view + 0x958);
    if (off == 0) {
        return 0;
    }
    return 9 * *(u8 *)(arg1 + off + 0x10);
}
