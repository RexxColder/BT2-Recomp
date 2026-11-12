#include "common.h"

extern u8 *D_004263E8 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

/* 0x003D8798: S = D_004263E8. For t5 = 0..3 with n = S->(0x6E00 + 4*t5 + 0xC) > 0: records E = S + a2, a2 = 0x1B24*t5 +
 * 0x170 + 0xC*t3 (t3 = 0 .. n-1): E->0x14 = (s16) D_387F2C[4*E->0xC + 0x1F32]; then twice (t2 = 0x6E20, 0x6E24):
 * if E->0xC == S->(t2+4): E->0x14 -= 1 and if that is negative, E->0x14 = 0. */
void func_003D8798(void) {
    s32 t5;
    s32 t3;
    s32 a2;

    for (t5 = 0; t5 < 4; t5++) {
        a2 = t5 * 0x1B24 + 0x170;
        if (*(s32 *)(D_004263E8 + t5 * 4 + 0x6E00 + 0xC) > 0) {
            t3 = 0;
            do {
                u8 *e = D_004263E8 + a2;
                s32 t2 = 0x6E20;
                s32 t0 = 1;

                *(s32 *)(e + 0x14) = *(s16 *)(D_387F2C + *(s32 *)(e + 0xC) * 4 + 0x1F32);
                do {
                    if (*(s32 *)(e + 0xC) == *(s32 *)(D_004263E8 + t2 + 4)) {
                        *(s32 *)(e + 0x14) = *(s32 *)(e + 0x14) - 1;
                        if (*(s32 *)(e + 0x14) < 0) {
                            *(s32 *)(e + 0x14) = 0;
                        }
                    }
                    t2 += 4;
                    t0 -= 1;
                } while (t0 >= 0);

                t3 += 1;
                a2 += 0xC;
            } while (t3 < *(s32 *)(D_004263E8 + t5 * 4 + 0x6E00 + 0xC));
        }
    }
}
