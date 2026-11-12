#include "common.h"

void func_002B5DC8(u8 *arg0) {
    s32 a2;
    s32 a3;
    s32 v0;
    u8 *a1;

    *(s32 *)(arg0 + 0xB4) = 0;
    *(s32 *)(arg0 + 0xB8) = 0;
    a1 = arg0 + 0xD0;
    *(s32 *)(arg0 + 0xBC) = 0;
    a3 = 0;
    a2 = 7;
    do {
        v0 = a3 + 0xC0;
        a3 += 0x14;
        a2 -= 1;
        *(s32 *)(a1 - 0x10) = 0;
        *(s32 *)(arg0 + 4 + v0) = 0;
        *(s32 *)(arg0 + 8 + v0) = 0;
        *(s32 *)(arg0 + 0xC + v0) = 0;
        *(s32 *)(a1 + 0) = 0x11;
        a1 += 0x14;
    } while (a2 >= 0);
}
