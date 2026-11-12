#include "common.h"

extern s32 func_00183228 __attribute__((section(".data")));

s32 func_00182C00(s32 arg0) {
    s32 var_v0;

    var_v0 = 0;
    if ((arg0 != 0) && (*(s32 *)(*(s32 *)(arg0 + 0x28)) == (s32)0x00183228u) &&
        ((*(u8 *)(arg0 + 0) & 1) == 0)) {
        var_v0 = (((*(u16 *)(*(s32 *)(arg0 + 0x38) + 0xAD6)) >> 0xC) ^ 1) & 1;
    }
    return var_v0;
}
