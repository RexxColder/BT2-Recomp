#include "common.h"

void func_001CCAC8(s32 arg0, s32 arg1);
void func_001CCB20(s32 arg0, s32 arg1);

void func_0019C060(u8 *arg0) {
    u8 *s1;
    u8 *slot;
    s32 s2;
    s32 a1;

    s2 = 1;
    s1 = *(u8 **)(arg0 + 0x38);
    slot = s1 + 0x34;
    do {
        s2 -= 1;
        func_001CCAC8(*(s32 *)slot, (s32)(s1 + 0x40));
        a1 = (s32)(s1 + 0x60);
        s1 += 0x10;
        func_001CCB20(*(s32 *)slot, a1);
        slot += 4;
    } while (s2 >= 0);
}
