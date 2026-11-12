#include "common.h"

void func_0029BAB0(u8 *arg0);
extern u8 *D_00387B00;

void func_00282058(void) {
    s32 s0 = 3;
    s32 s1 = 0;

    do {
        u8 *a0 = D_00387B00 + s1;
        u8 v3;

        s1 += 0x60;
        v3 = *(u8 *)(a0 + 0x58);
        if ((v3 & 1) && (v3 & 8)) {
            *(u8 *)(a0 + 0x58) = 0;
            func_0029BAB0(a0 + 0x40);
        }
        s0 -= 1;
    } while (s0 >= 0);
}
