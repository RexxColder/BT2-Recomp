#include "common.h"

s32 func_002C2000(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_0037A0B0[] __attribute__((section(".data")));
extern u8 D_0037A0C0[] __attribute__((section(".data")));
extern u8 D_0037A1C0[] __attribute__((section(".data")));

s32 func_002C1EA0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[4];
    s32 temp_v1;
    s32 prod;
    s32 var_v0;

    if (func_002C2000(sp, arg0, arg1, arg3) == 0) {
        return -1;
    }
    temp_v1 = *(s32 *)(D_0037A0C0 + ((sp[0] * 16 + sp[2]) * 4));
    var_v0 = -1;
    if (temp_v1 != -1) {
        prod = *(s32 *)(D_0037A1C0 + sp[0] * 4) * temp_v1;
        var_v0 = (prod * 0x3E8) / (*(s32 *)(D_0037A0B0 + sp[3] * 4) * 8);
    }
    return var_v0;
}
