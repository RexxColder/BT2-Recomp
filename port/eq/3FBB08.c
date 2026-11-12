#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));

/* 0x003FBB08: for arg0 in 0..5 returns x*c + c with x = D_3876A4->0x58 and c = 100, 50, 40, 30, 20, 10 (jump table
 * order); any other index returns 0. */
s32 func_003FBB08(s32 arg0) {
    s32 x;

    if ((u32)arg0 >= 6) {
        return 0;
    }

    x = *(s32 *)(D_3876A4 + 0x58);
    switch (arg0) {
    case 0:
        return x * 100 + 100;
    case 1:
        return x * 50 + 50;
    case 2:
        return x * 40 + 40;
    case 3:
        return x * 30 + 30;
    case 4:
        return x * 20 + 20;
    default:
        return x * 10 + 10;
    }
}
