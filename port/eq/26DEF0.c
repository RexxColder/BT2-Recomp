#include "common.h"

void func_0026C680(u8 *arg0, s32 arg1);

void func_0026DEF0(u8 *arg0) {
    s32 s1 = 0;
    s32 s2 = 0;

    *(s32 *)(arg0 + 8) = 0;
    *(s8 *)(arg0 + 0x11) = 0;
    if (*(u16 *)(arg0 + 0x12) != 0) {
        do {
            u8 *a0;
            s32 a1;

            s2 += 1;
            a0 = *(u8 **)(arg0 + 0x14) + s1;
            a1 = *(s32 *)arg0;
            s1 += 0xC;
            func_0026C680(a0, a1);
        } while (s2 < *(u16 *)(arg0 + 0x12));
    }
}
