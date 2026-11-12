#include "common.h"

u8 *func_00101A88(s32 arg0);
void func_0028BB60(s32 arg0);

void func_001020F0(void) {
    s32 s2;
    s32 s1;
    u8 *s0;

    s2 = 0;
    do {
        s1 = 4;
        s0 = func_00101A88(s2) + 0x50;
        for (;;) {
            if (*(s32 *)(s0 + 8) != 0) {
                func_0028BB60(*(s32 *)(s0 + 8));
                *(s32 *)(s0 + 8) = 0;
            }
            s1 -= 1;
            if (*(s32 *)(s0 + 0xC) != 0) {
                func_0028BB60(*(s32 *)(s0 + 0xC));
                *(s32 *)(s0 + 0xC) = 0;
            }
            s0 += 0x58;
            if (s1 < 0) {
                break;
            }
        }
        s2 += 1;
    } while (s2 < 2);
}
