#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));
extern u8 D_00423130 __attribute__((section(".data")));

void *memcpy(void *, const void *, unsigned int);

/* 0x003C6670: buf[8] (s32) = copy of the 32 bytes at D_00423130. For i in 0..7: *(G + 4*buf[i] + 0xC4) = 0 (G = D_00423114).
 * Then i = 0 while i < G->0x3644: B = G->0x10 (pointer), ci = *(G + 0x3648 + 4i), z = *(B + 4*ci + 4) & ~3,
 * *(G + 4*buf[i] + 0xC4) = *(B + z + 0x10). */
void func_003C6670(void) {
    s32 buf[8];
    s32 i;

    memcpy(buf, &D_00423130, 0x20);

    for (i = 0; i < 8; i++) {
        *(s32 *)(D_00423114 + buf[i] * 4 + 0xC4) = 0;
    }

    i = 0;
    while (i < *(s32 *)(D_00423114 + 0x3644)) {
        u8 *gg = D_00423114;
        u8 *bptr = *(u8 **)(gg + 0x10);
        s32 ci = *(s32 *)(gg + 0x3648 + i * 4);
        s32 z = (s32)((u32)*(s32 *)(bptr + ci * 4 + 4) & ~3u);
        s32 w = *(s32 *)(bptr + z + 0x10);

        *(s32 *)(gg + buf[i] * 4 + 0xC4) = w;
        i++;
    }
}
