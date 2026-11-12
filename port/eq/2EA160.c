#include "common.h"

s32 strlen(s32 arg0);
extern u8 D_0039D6A0[] __attribute__((section(".data")));

void func_002EA160(s32 arg0, s32 arg1, s32 arg2) {
    u8 *buf;
    s32 a0;
    s32 a1;
    s32 a3;
    s32 len;

    buf = (u8 *)arg1;
    *buf = (u8)(arg0 % 10);
    a0 = arg0 / 10;
    a1 = 0;
    if (a0 != 0) {
        a1 = 1;
        while (a1 < 0x20) {
            buf[a1] = (u8)(a0 % 10);
            a0 = a0 / 10;
            if (a0 == 0) {
                buf[a1] = 0;
                break;
            }
            a1 += 1;
        }
    } else {
        buf[0] = 0;
    }

    len = strlen((s32)D_0039D6A0);
    a3 = arg2 - 1;
    if (len < a3) {
        a3 = len;
    }
    for (a1 = 0; a1 < a3; a1++) {
        buf[a1] = D_0039D6A0[a3 - 1 - a1];
    }
    buf[a1] = 0;
}
