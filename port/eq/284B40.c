#include "m2c_macros.h"

extern u8 D_00388F30[] __attribute__((section(".data")));

void Dma_AddZbuf(s32 a0, s32 a1);
void FadeSlot_CalcColor(u8 *slot);
s32 Ramp_Step(u8 *p);
void func_0029BAB0(u8 *p);
void func_002848C0(s32 a0, u8 *slot);

/* float -> s32 bits as the asm does it: trunc, with the 2^31 split for large values */
#define FADE_F2I(f) (((f) >= 2147483648.0f) ? ((s32)((f) - 2147483648.0f) | (s32)0x80000000u) : (s32)(f))

void func_00284B40(void) {
    u8 *s0;
    s32 i;
    s32 found;

    found = (D_00388F30[0x58] != 0) || (D_00388F30[0x58 + 0x60] != 0);
    if (!found) {
        return;
    }
    for (i = 0; i < 2; i++) {
        s0 = D_00388F30 + i * 0x60;
        if (s0[0x58] == 0) {
            continue;
        }
        if (s0[0x58] & 8) {
            FadeSlot_CalcColor(s0);
            if (FADE_F2I(*(f32 *)(s0 + 0xC)) == 0) {
                s0[0x58] = 0;
                func_0029BAB0(s0 + 0x40);
            }
        } else {
            if (Ramp_Step(s0 + 0x40) == 1) {
                s0[0x58] = s0[0x58] | 8;
            }
        }
    }
    Dma_AddZbuf(0xE0, 1);
    for (i = 0; i < 2; i++) {
        s0 = D_00388F30 + i * 0x60;
        if (s0[0x58] != 0) {
            FadeSlot_CalcColor(s0);
            func_002848C0(0x44, s0);
        }
    }
    Dma_AddZbuf(0xE0, 0);
}
