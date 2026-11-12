#include "common.h"

extern void **D_0038780C;

s32 func_001A1210(s32 arg0) {
    s32 var_v0;
    u8 *temp_a0;
    void *temp_v1;

    temp_v1 = D_0038780C[arg0];
    var_v0 = 0;
    if (temp_v1 != NULL) {
        temp_a0 = *(u8 **)((u8 *)temp_v1 + 0x38);
        var_v0 = 1;
        *(s32 *)(temp_a0 + 0x40) = *(s32 *)(temp_a0 + 0x40) | 2;
    }
    return var_v0;
}
