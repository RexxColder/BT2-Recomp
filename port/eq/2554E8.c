#include "common.h"

void func_0026E9E8(u8 *arg0);
extern u8 *D_003879D0;

void func_002554E8(void) {
    s32 s0;
    s32 s1;
    s32 a2;
    u8 *d;
    u8 *t;

    s0 = 1;
    s1 = 0;
    do {
        s0 -= 1;
        d = D_003879D0 + s1;
        s1 += 0x28;
        func_0026E9E8(d + 0x28);
    } while (s0 >= 0);
    a2 = 0x1A0;
    s0 = 4;
    *(s32 *)(D_003879D0 + 0x278) = 0;
    do {
        t = D_003879D0 + a2;
        a2 += 0x14;
        if (*(s32 *)t >= 0) {
            *(s32 *)(D_003879D0 + 0x278) = *(s32 *)(D_003879D0 + 0x278) + *(s32 *)(t + 0x4);
        }
        s0 -= 1;
    } while (s0 >= 0);
}
