#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));

void func_003EA430(s32 arg0);
void func_26E9E8(u8 *arg0);

/* 0x003EB118: G = D_00428F48, flags = G->0x194. If flags & 0x80: G->0x1BC -= 0.075f (bits 0x3D999999); if it is then
 * below 0: G->0x1BC = 0, func_003EA430(flags), G->0x194 &= ~0x80. Else if flags & 0x40: G->0x1BC += 0.075f, clamped
 * to 1.0f. Then func_26E9E8(G + 0x28*j + 0x28) for j = 0..4. */
void func_003EB118(void) {
    f32 k;
    s32 flags;
    s32 j;

    *(u32 *)&k = 0x3D999999u;
    flags = *(s32 *)(D_00428F48 + 0x194);

    if (flags & 0x80) {
        *(f32 *)(D_00428F48 + 0x1BC) = *(f32 *)(D_00428F48 + 0x1BC) - k;
        if (*(f32 *)(D_00428F48 + 0x1BC) < 0.0f) {
            *(f32 *)(D_00428F48 + 0x1BC) = 0.0f;
            func_003EA430(flags);
            *(s32 *)(D_00428F48 + 0x194) = *(s32 *)(D_00428F48 + 0x194) & ~0x80;
        }
    } else if (flags & 0x40) {
        *(f32 *)(D_00428F48 + 0x1BC) = *(f32 *)(D_00428F48 + 0x1BC) + k;
        if (1.0f < *(f32 *)(D_00428F48 + 0x1BC)) {
            *(f32 *)(D_00428F48 + 0x1BC) = 1.0f;
        }
    }

    for (j = 0; j < 5; j++) {
        func_26E9E8(D_00428F48 + j * 0x28 + 0x28);
    }
}
