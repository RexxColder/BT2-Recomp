#include "common.h"

s32 func_003D6560(u8 *arg0, s32 arg1);

/* 0x003D76A8: P = arg0. Walks 15 records (s1 = P+0x3540 + 0x10*k reads u16 at s1-2 and s1; s2 = P+0x353C + 0x10*k):
 * when the flag word at P + (idx<<5) + 0x333C has bit 0 for the first index (s1-2) or else the second (s1), use
 * v = *s2; otherwise call func_003D6560(P, k) and use v = *s2. With v & 2: s3++, and return when P->0x3320 < s3.
 * k++ each step. */
void func_003D76A8(u8 *arg0) {
    u8 *s1;
    u8 *s2;
    s32 s3;
    s32 s4;
    u16 v;

    s1 = arg0 + 0x3540;
    s2 = arg0 + 0x353C;
    s3 = 0;
    s4 = 0;

    do {
        if (*(u16 *)(arg0 + ((s32)*(u16 *)(s1 - 2) << 5) + 0x333C) & 1) {
            v = *(u16 *)s2;
        } else if (*(u16 *)(arg0 + ((s32)*(u16 *)s1 << 5) + 0x333C) & 1) {
            v = *(u16 *)s2;
        } else {
            func_003D6560(arg0, s4);
            v = *(u16 *)s2;
        }

        if (v & 2) {
            s3 += 1;
            if (*(s32 *)(arg0 + 0x3320) < s3) {
                return;
            }
        }

        s4 += 1;
        s2 += 0x10;
        s1 += 0x10;
    } while (s4 < 0xF);
}
