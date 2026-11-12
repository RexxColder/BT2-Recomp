#include "common.h"

s32 func_00125FF0(s32 arg0);

s32 func_001214F8(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = func_00125FF0(arg0);
    if (var_v0 != 0) {
        *(u8 *)(arg1 + 0) = *(u8 *)(var_v0 + 0x10);
        *(u8 *)(arg1 + 1) = *(u8 *)(var_v0 + 0x11);
        *(u8 *)(arg1 + 2) = *(u8 *)(var_v0 + 0x12);
        *(u8 *)(arg1 + 3) = *(u8 *)(var_v0 + 0x13);
        var_v0 = *(s32 *)(var_v0 + 0x14);
    }
    return var_v0;
}
