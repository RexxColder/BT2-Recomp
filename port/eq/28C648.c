#include "common.h"

extern u8 *D_003876A0;
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_0028C4B8(s32 arg0);

s32 func_0028C648(void) {
    s32 s0 = 0;
    s32 s2 = 0;
    s32 s4 = 2;
    u8 *s1;
    s32 v0;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 2) == 0) {
        s4 = 1;
    }
    if (s4 != 0) {
        s1 = D_003B0B00 + 0x104;
        v0 = *(s32 *)s1;
        do {
            s1 += 0x180;
            if (v0 != 1 || func_0028C4B8(s0) != 0) {
                s2 |= 1 << s0;
            }
            s0 += 1;
            v0 = *(s32 *)s1;
        } while (s0 < s4);
    }
    if ((s2 & 3) == 3) {
        return 3;
    }
    if (s2 & 2) {
        return 2;
    }
    return (s2 & 1) != 0;
}
