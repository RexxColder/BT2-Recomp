#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);
extern f32 D_0038595C;

f32 func_002086B0(s32 arg0) {
    u8 *view = (u8 *)BtlObjVis_GetView_207EA0(arg0);
    f32 f1;
    f32 result = 0.0f;

    if (view != 0) {
        f1 = *(f32 *)(*(s32 *)(view + 0x958) + 0x48);
        result = f1;
        if (f1 < 0.0f) {
            result = *(f32 *)(view + 0xFA8) * D_0038595C;
        }
    }
    return result;
}
