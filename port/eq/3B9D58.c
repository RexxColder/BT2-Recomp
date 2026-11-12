#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

void func_2982E8(u8 *arg0);
void McCard_Checksum(u8 *arg0, s32 arg1, s32 arg2);

/* 0x003B9D58 (G = D_004213B0): func_2982E8(G+0xF8). For i = 0..0x242: a2 = i*4 + 0x2020; u16 at G+a2+0xA =
 * u16 (G->0xC)[i]; the u16 at G+a2+8 gets |= 3 when the s16 just copied is nonzero, &= ~3 otherwise. Then
 * McCard_Checksum(G+0xF8, 0x4000, 1) and the 0x4000 bytes G+0xF8 are copied to *D_00387F2C. */
void func_003B9D58(void) {
    u8 *g;
    s32 i;
    s32 a2;

    g = D_004213B0;
    func_2982E8(g + 0xF8);
    for (i = 0; i < 0x243; i++) {
        a2 = i * 4 + 0x2020;
        *(u16 *)(g + a2 + 0xA) = *(u16 *)(*(u8 **)(g + 0xC) + i * 4);
        if (*(s16 *)(g + a2 + 0xA) != 0) {
            *(u16 *)(g + 8 + a2) = *(u16 *)(g + 8 + a2) | 0x3;
        } else {
            *(u16 *)(g + 8 + a2) = *(u16 *)(g + 8 + a2) & ~0x3;
        }
    }
    McCard_Checksum(g + 0xF8, 0x4000, 1);
    memcpy(D_00387F2C, g + 0xF8, 0x4000);
}
