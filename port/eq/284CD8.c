#include "common.h"

extern u8 D_00388FF0 __attribute__((section(".data")));
extern u8 *D_003876A0;
s32 FadeSlot_CalcColor(u8 *arg0);
void func_0029BAB0(u8 *arg0);
s32 Ramp_Step(u8 *arg0);
s32 Dma_AddZbuf(s32 arg0, s32 arg1);
void func_002848C0(s32 arg0, u8 *arg1);

/* 0x00284CD8: state block G = D_00388FF0 (byte +0x58 = flags, float +0xC, sub-block +0x40). Nothing when G.flags is 0.
 * Unless the 64-bit word at D_003876A0+0x4D8 has bit 0x100: flags & 8 -> FadeSlot_CalcColor(G) and the float at +0xC
 * converted to an integer; when that is 0, func_0029BAB0(G+0x40) and flags = 0, return. Otherwise, when
 * Ramp_Step(G+0x40) == 1, flags |= 8. Then, while flags is non-zero: Dma_AddZbuf(0xE0, 1), FadeSlot_CalcColor(G),
 * func_002848C0(0x44, G), Dma_AddZbuf(0xE0, 0). */
void func_00284CD8(void) {
    u8 *g = &D_00388FF0;
    u32 v;
    f32 f;

    if (g[0x58] == 0) {
        return;
    }
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        if (g[0x58] & 8) {
            FadeSlot_CalcColor(g);
            f = *(f32 *)(g + 0xC);
            if (f >= 2147483648.0f) {
                v = ((u32)(s32)(f - 2147483648.0f)) | 0x80000000u;
            } else {
                v = (u32)(s32)f;
            }
            if (v == 0) {
                func_0029BAB0(g + 0x40);
                g[0x58] = 0;
                return;
            }
        } else {
            if (Ramp_Step(g + 0x40) == 1) {
                g[0x58] |= 8;
            }
        }
    }
    if (g[0x58] == 0) {
        return;
    }
    Dma_AddZbuf(0xE0, 1);
    FadeSlot_CalcColor(g);
    func_002848C0(0x44, g);
    Dma_AddZbuf(0xE0, 0);
}
