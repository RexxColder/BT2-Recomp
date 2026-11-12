#include "common.h"
#include "sys/dma.h"

void func_0027E6E0(void *arg0);
void func_0027F6D0(void *arg0);
void func_0027F6E8(void *arg0);
extern u8 *D_00387AFC;
extern u8 *D_003876A0;

/* 0x00280E90: if the byte at +0x3CCA of the block is 0: set the scissor (0..0x1FF, 0..0x1BF), run the two
 * sub-setups at +0x2500 and +0x1B40, and when bit 43 of the 64-bit word at D_003876A0 +0x4D8 is clear run
 * func_0027F6E8(+0x2500) and set the byte at +0x3CC0 to 1. */
void func_00280E90(void) {
    if (D_00387AFC[0x3CCA] == 0) {
        Dma_AddScissor(0, 0x1FF, 0, 0x1BF);
        func_0027F6D0(D_00387AFC + 0x2500);
        func_0027E6E0(D_00387AFC + 0x1B40);
        if ((*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 43)) == 0) {
            func_0027F6E8(D_00387AFC + 0x2500);
            D_00387AFC[0x3CC0] = 1;
        }
    }
}
