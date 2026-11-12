#include "common.h"

extern u8 *D_0042A584 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

/* word lookup: *(s32 *)(Q + (w & ~3) + 0x10) with w = *(u32 *)(Q + idx * 4 + 4) */
#define LOOKUP(q, idx) (*(s32 *)((q) + (*(u32 *)((q) + (idx) * 4 + 4) & ~3u) + 0x10))

/* 0x003FA6B0: five-pass fill of the P->0xA4..0xDC slots from the T table (entries 0xC bytes, 0x200 base) */
void func_003FA6B0(void) {
    u8 *P = D_0042A584;
    u8 *T = D_387F2C;
    s32 i;

    for (i = 0; i < 5; i++) {
        s32 o4 = 0xDC - 4 * i;
        s32 o8a = 0xC8 - 8 * i;
        s32 o8b = 0xC4 - 8 * i;
        s32 a = *(s32 *)(P + 0x110);
        s32 j = *(s32 *)(P + a * 4 + 0x114) + i;
        u8 *e = T + ((a * 0xF + j) * 4) + 0x200;

        if (e[0xC] < 0x86) {
            if (*(s32 *)(*(u8 **)(P + 0x130) + j * 0x38 + 0xC) == 2) {
                *(s32 *)(P + o4) = 0;
                if (*(u16 *)(e + 0xE) != 0) {
                    *(s32 *)(P + o8a) = LOOKUP(*(u8 **)(P + 0x10), e[0xC]);
                    a = *(s32 *)(P + 0x110);
                    j = *(s32 *)(P + a * 4 + 0x114) + i;
                    *(s32 *)(P + o8b) = LOOKUP(*(u8 **)(P + 0x10), T[(a * 0xF + j) * 4 + 0x20D]);
                } else {
                    *(s32 *)(P + o8a) = 0;
                    *(s32 *)(P + o8b) = 0;
                }
            } else {
                if (*(u16 *)(e + 0xE) != 0) {
                    *(s32 *)(P + o4) = LOOKUP(*(u8 **)(P + 0x10), e[0xC]);
                } else {
                    *(s32 *)(P + o4) = 0;
                }
                *(s32 *)(P + o8a) = 0;
                *(s32 *)(P + o8b) = 0;
            }
        }
    }
}
