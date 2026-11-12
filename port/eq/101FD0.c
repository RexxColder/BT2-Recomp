#include "common.h"

s32 func_00101A88(s32 arg0);
s32 func_0028BAA8(s32 arg0);
s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
void func_00101F60(void);

void func_00101FD0(void) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s4;
    s32 v1;
    u32 q;

    s4 = 0;
    do {
        s1 = 4;
        s0 = func_00101A88(s4) + 0x50;
        do {
            s1 -= 1;
            *(s32 *)(s0 + 0x8) = func_0028BAA8(0x1000);
            *(s32 *)(s0 + 0xC) = func_0028BAA8(0x1000);
            s0 += 0x58;
        } while (s1 >= 0);
        s4 += 1;
    } while (s4 < 2);

    s4 = 0;
    do {
        s2 = func_00101A88(s4);
        v1 = *(s32 *)s2;
        if (v1 >= 2) {
            s1 = 0;
            if (v1 > 0) {
                s0 = s2 + 0x50;
                do {
                    s1 += 1;
                    q = ((u32)*(u32 *)(s0 - 0x48) / 9u) * 2u;
                    *(s32 *)(s0 + 0x8) = func_00100ED0(
                        (((s4 ^ 1) == 0) ? ((s32)q + 1) : (s32)q) + 0x3CC2,
                        *(s32 *)(s0 + 0x8), 0);
                    s0 += 0x58;
                } while (s1 < *(s32 *)s2);
            }
        }
        s4 += 1;
    } while (s4 < 2);
    func_00101F60();
}
