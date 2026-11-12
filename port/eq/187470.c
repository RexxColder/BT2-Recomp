#include "common.h"

void func_00187470(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *a2p = arg1 + arg2 * 0x10;
    u8 *a3p = arg1 + arg3 * 0x10;

    *(s8 *)(arg0 + 0x198) = (s8)arg3;
    *(u8 **)(arg0 + 0) = arg1;
    *(s64 *)(arg0 + 0x8) = *(s64 *)(a2p + 0);
    *(s64 *)(arg0 + 0x10) = *(s64 *)(a2p + 8);
    *(s64 *)(arg0 + 0x18) = *(s64 *)(a3p + 0);
    *(s64 *)(arg0 + 0x20) = *(s64 *)(a3p + 8);
}
