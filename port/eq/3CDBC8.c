#include "common.h"

extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_0042311C __attribute__((section(".data")));

s32 func_298460(s32 a0, s32 a1, s32 a2);

#define TAIL_TABLE(X, FLAGS)                                                              \
    do {                                                                                  \
        q = D_0042311C;                                                                   \
        *(u32 *)(q + 0x118) = *(u32 *)(q + 0x118) | (FLAGS);                              \
        *(s32 *)(q + 0x130) = (X);                                                        \
        return func_298460((X), *(s32 *)(*(u8 **)(q + 0x140) + 48 * (X) + 0x10), 1);      \
    } while (0)

s32 func_003CDBC8(void) {
    u8 *p;
    u8 *q;
    s32 m;
    s32 a2;
    s32 st;

    m = *(s32 *)(D_003876A4 + 0x90);
    if (m == 1) {
        a2 = 2;
    } else if (m < 2) {
        a2 = (m == 0) ? 1 : 0;
    } else if (m == 2) {
        a2 = 3;
    } else if (m == 3) {
        a2 = 4;
    } else {
        a2 = 0;
    }

    p = D_00387F2C;
    *(u16 *)(p + 0x426) = (u16)(*(u16 *)(p + 0x426) + a2);

    p = D_00387F2C;
    st = (s32)*(s16 *)(p + 0x424);
    if ((u32)st < 6) {
        switch (st) {
        case 0:
            if (*(s16 *)(p + 0x426) < 3) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            q = D_0042311C;
            *(u32 *)(q + 0x118) = *(u32 *)(q + 0x118) | 0x30;
            *(s32 *)(q + 0x130) = 0x22F;
            return func_298460(*(s32 *)(q + 0x130), 1, 1);
        case 1:
            if (*(s16 *)(p + 0x426) < 6) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            q = D_0042311C;
            *(u32 *)(q + 0x118) = *(u32 *)(q + 0x118) | 0x30;
            *(s32 *)(q + 0x130) = 0x230;
            return func_298460(*(s32 *)(q + 0x130), 1, 1);
        case 2:
            if (*(s16 *)(p + 0x426) < 9) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            q = D_0042311C;
            *(u32 *)(q + 0x118) = *(u32 *)(q + 0x118) | 0x10;
            *(s32 *)(q + 0x130) = 0x231;
            return func_298460(*(s32 *)(q + 0x130), 1, 1);
        case 3:
            if (*(s16 *)(p + 0x426) < 0xC) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            TAIL_TABLE(0xFC, 0x10);
        case 4:
            if (*(s16 *)(p + 0x426) < 0x12) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            q = D_0042311C;
            *(u32 *)(q + 0x118) = *(u32 *)(q + 0x118) | 0x10;
            *(s32 *)(q + 0x130) = 0x232;
            return func_298460(*(s32 *)(q + 0x130), 1, 1);
        case 5:
            if (*(s16 *)(p + 0x426) < 0x1E) {
                return 1;
            }
            *(u16 *)(p + 0x424) = (u16)(*(u16 *)(p + 0x424) + 1);
            *(u16 *)(p + 0x426) = (u16)(*(u16 *)(p + 0x426) - 0x1E);
            TAIL_TABLE(0xDE, 0x10);
        }
    }

    /* default (L3CDF00) */
    if (*(s16 *)(p + 0x426) < 0xA) {
        return 1;
    }
    *(u16 *)(p + 0x426) = (u16)(*(u16 *)(p + 0x426) - 0xA);
    TAIL_TABLE(0xE5, 0x10);
}
