#include "common.h"

s32 func_002AC668(void *a0, s32 a1, s32 a2, void *a3);
extern u8 D_003B26B0 __attribute__((section(".data")));

s32 func_002ACB20(void) {
    u8 *s1;
    u8 *s0;
    s32 buf[4];
    s32 st;

    s1 = &D_003B26B0;
    s0 = s1 - 0x5C;
    st = *(s32 *)s1;
    switch (st) {
    case 0:
    case 1:
    case 3:
        *(s8 *)(s0 + 0x20) = 0;
        return 0;
    case 2:
        func_002AC668(*(void **)(s0 + 4), 0, 0, buf);
        if (buf[0] != 2) {
            return 0;
        }
        if (*(s32 *)(s1 + 0x24) != buf[0]) {
            *(s8 *)(s0 + 0x20) = 0;
            return 1;
        }
        *(s8 *)(s0 + 0x20) = 1;
        return 0;
    case 4:
        if (*(u8 *)(s0 + 0x20) == 0) {
            return 0;
        }
        *(s8 *)(s0 + 0x20) = 0;
        return 1;
    default:
        return 0;
    }
}
