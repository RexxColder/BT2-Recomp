#include "common.h"

s32 func_002CA8A8(u8 *arg0, u8 *arg1, s32 *arg2);
s32 func_002D07B0(u8 *arg0, s32 arg1);

s32 func_002CA838(u8 *arg0) {
    s32 sp0 = 0;
    u8 *s0 = *(u8 **)(arg0 + 0x1FC0);
    s32 v0 = func_002CA8A8(arg0, s0, &sp0);

    if (v0 != 0) {
        return v0;
    }
    *(s32 *)(s0 + 0x74) = 2;
    if (sp0 != 0 && func_002D07B0(arg0, 0x30) != 0) {
        *(s32 *)(s0 + 0x78) = 0xC8;
    } else {
        *(s32 *)(s0 + 0x78) = 0xC0;
    }
    return 0;
}
