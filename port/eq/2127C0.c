#include "common.h"

extern u8 *D_003876A0 __attribute__((section(".data")));
extern u8 *gBtlCam __attribute__((section(".data")));

s32 func_002127C0(void *arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 2)) {
        var_v0 = *(s32 *)((u8 *)arg0 + 0x1534) == *(s32 *)(*(u8 **)(gBtlCam + 0x600) + 0x254);
    }
    return var_v0;
}
