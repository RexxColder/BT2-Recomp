#include "common.h"

void func_002BFE48(void *a0, s32 a1, s32 a2);

void func_002BFC18(void *arg0, void *arg1, void *arg2, void *arg3, s32 arg4) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    s32 k;

    s0 = (u8 *)arg1 + 116 * arg4;
    s1 = (u8 *)arg2 + 4 * arg4;
    s2 = (u8 *)arg3 + 4 * arg4;
    func_002BFE48(s0, 1, *(s32 *)s2 != 0);
    s0 += 0x10;
    *(s32 *)(s0 + 0) = *(s32 *)s1;
    *(s32 *)(s0 + 4) = *(s32 *)s2;
    *(s32 *)(s0 + 8) = 0;
    *(s32 *)(s0 + 0xC) = 0;
    *(void **)(s0 + 0x10) = (u8 *)arg0 + 0x16B0;
    s3 = (u8 *)arg0 + 0x1EA8;
    for (k = 0; k < 16; k++) {
        *(s32 *)s3 = 0;
        s3 -= 0x88;
    }
}
