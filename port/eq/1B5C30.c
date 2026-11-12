#include "common.h"

s32 func_001B5CF0(void *a0);
extern u8 *gEftShotFx;
extern u8 *D_003876A0;

void func_001B5C30(void) {
    u8 *s0;
    u8 *s1;
    u8 *prev;
    u8 *next;
    s32 r;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    s1 = *(u8 **)(gEftShotFx + 0x54);
    while (s1 != NULL) {
        s0 = s1;
        r = func_001B5CF0(s0);
        s1 = *(u8 **)(s0 + 0x50);
        if (r != 0) {
            *(s32 *)(s0 + 0x48) = 0;
            prev = *(u8 **)(s0 + 0x4C);
            if (prev != NULL) {
                *(u8 **)(prev + 0x50) = *(u8 **)(s0 + 0x50);
            } else {
                *(u8 **)(gEftShotFx + 0x54) = s1;
            }
            next = *(u8 **)(s0 + 0x50);
            if (next != NULL) {
                *(u8 **)(next + 0x4C) = prev;
            } else {
                *(u8 **)(gEftShotFx + 0x58) = prev;
            }
            *(u8 **)(s0 + 0x50) = NULL;
            *(u8 **)(s0 + 0x4C) = NULL;
            *(s32 *)(gEftShotFx + 0x8) = *(s32 *)(gEftShotFx + 0x8) - 1;
        }
    }
}
