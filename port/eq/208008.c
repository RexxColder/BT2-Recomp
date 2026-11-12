#include "common.h"

s32 BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_00208008(s32 arg0, s32 arg1) {
    s32 temp_v1;
    s32 temp_a0;
    s32 var_v0;

    var_v0 = BtlObjVis_GetView_207EA0(arg0);
    temp_a0 = var_v0;
    if (temp_a0 != 0) {
        temp_v1 = *(s32 *)(temp_a0 + 0x958);
        var_v0 = 0;
        if (temp_v1 != 0) {
            var_v0 = (*(u8 *)(temp_v1 + arg1) * 9) + *(s32 *)(temp_a0 + 8);
        }
    }
    return var_v0;
}
