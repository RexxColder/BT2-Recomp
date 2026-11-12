#include "common.h"

extern u8 *D_003876B4;

typedef s32 (*Callback)(s32, s32);

s32 func_00105500(s32 arg0, s32 arg1) {
    u8 *base;
    s32 temp_v0;
    s32 var_v0;

    var_v0 = -1;
    if (arg0 != 0) {
        base = *(u8 **)(D_003876B4 + 0x104);
        temp_v0 = *(s32 *)(base + (arg1 * 0x14) + 0x10);
        if (temp_v0 == 0) {
            *(s32 *)(D_003876B4 + 0x4) = 0;
            *(u8 **)(D_003876B4 + 0x8) = NULL;
        } else {
            *(s32 *)(D_003876B4 + 0x4) = temp_v0;
            *(u8 **)(D_003876B4 + 0x8) = D_003876B4 + 0x108;
        }
        /* a1 is not written here: the function's own second parameter, passed through */
        var_v0 = ((Callback)arg0)((s32)(D_003876B4 + 0x4), arg1);
    }
    return var_v0;
}
