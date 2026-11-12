#include "common.h"

extern u8 *D_004279D0 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);

/* 0x003E7610: G = D_004279D0, k = 0.075f (bits 0x3D999999). Field 0x30C: if G->0xF0 has bit 8, x -= k and x < 0 -> 0;
 * else x += k and x > 1.0 -> 1.0. Field 0x308: if G->0xF0 has bit 0x10, x -= k, and x < 0 -> 0 with bit 0x10 cleared;
 * else x += k and x > 1.0 -> 1.0. Then func_26E9E8(G + 0x10). */
void func_003E7610(void) {
    f32 k;
    f32 x;

    *(u32 *)&k = 0x3D999999u;

    if (*(s32 *)(D_004279D0 + 0xF0) & 8) {
        x = *(f32 *)(D_004279D0 + 0x30C) - k;
        *(f32 *)(D_004279D0 + 0x30C) = x;
        if (*(f32 *)(D_004279D0 + 0x30C) < 0.0f) {
            *(f32 *)(D_004279D0 + 0x30C) = 0.0f;
        }
    } else {
        x = *(f32 *)(D_004279D0 + 0x30C) + k;
        *(f32 *)(D_004279D0 + 0x30C) = x;
        if (1.0f < *(f32 *)(D_004279D0 + 0x30C)) {
            *(f32 *)(D_004279D0 + 0x30C) = 1.0f;
        }
    }

    if (*(s32 *)(D_004279D0 + 0xF0) & 0x10) {
        x = *(f32 *)(D_004279D0 + 0x308) - k;
        *(f32 *)(D_004279D0 + 0x308) = x;
        if (*(f32 *)(D_004279D0 + 0x308) < 0.0f) {
            *(f32 *)(D_004279D0 + 0x308) = 0.0f;
            *(s32 *)(D_004279D0 + 0xF0) = *(s32 *)(D_004279D0 + 0xF0) & ~0x10;
        }
    } else {
        x = *(f32 *)(D_004279D0 + 0x308) + k;
        *(f32 *)(D_004279D0 + 0x308) = x;
        if (1.0f < *(f32 *)(D_004279D0 + 0x308)) {
            *(f32 *)(D_004279D0 + 0x308) = 1.0f;
        }
    }

    func_26E9E8(D_004279D0 + 0x10);
}
