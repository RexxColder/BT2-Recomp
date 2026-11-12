#include "common.h"

void func_0025E190(s32 arg0, s32 arg1);
extern s32 D_00387A40;

void func_0025E1E8(void) {
    s32 s0 = 0;
    s32 s1 = 0;
    s32 a0;

    if (*(s32 *)(D_00387A40 + 0xC) <= 0) {
        return;
    }
    do {
        a0 = *(s32 *)(D_00387A40 + 8) + s0;
        s0 += 0x1520;
        if (*(s32 *)(a0 + 0xC) != 0) {
            func_0025E190(a0, 0);
        }
        s1 += 1;
    } while (s1 < *(s32 *)(D_00387A40 + 0xC));
}
