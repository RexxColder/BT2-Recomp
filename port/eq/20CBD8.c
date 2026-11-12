#include "common.h"

void *BtlObjVis_GetView_207EA0(s32 arg0);

s32 func_0020CBD8(s32 arg0) {
    void *var_v0;

    var_v0 = BtlObjVis_GetView_207EA0(arg0);
    if (var_v0 != NULL) {
        var_v0 = (void *)((*(s64 *)((u8 *)var_v0 + 0xAF0) & 0x102) == 0x102);
    }
    return (s32)var_v0;
}
