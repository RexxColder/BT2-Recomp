#include "common.h"

u8 func_001E03E0(u8 *arg0, u32 arg1, u8 *arg2);

s32  func_001E0300(u8 *arg0, s32 arg1) {
    u32 a1 = arg1 & 0xFF;
    u8 v0 = 0;

    if (a1 < *(u8 *)(arg0 + 0x10F00)) {
        u8 *s0 = arg0 + a1 * 0x21E0;

        v0 = *(u8 *)(s0 + 0x21DD);
        if (v0 != 0) {
            *(u8 *)(s0 + 0x21DD) = func_001E03E0(s0, a1, arg0);
            v0 = *(u8 *)(s0 + 0x21DD);
        }
    }
    return (u8)(v0);
}
