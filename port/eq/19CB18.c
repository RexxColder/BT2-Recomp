#include "common.h"

/* float (0..255 range, or up to 2^32) to a byte, as the MIPS unsigned conversion does it:
 * values at or above 2^31 are converted with the 2^31 bias, truncation as cvt.w.s */
#define CONV_U8(f) ((u8)(((f) >= 2147483648.0f ? ((u32)(s32)((f) - 2147483648.0f) | 0x80000000u) \
                                              : (u32)(s32)(f)) & 0xFF))

s32 func_001EC368(s32 arg0, s32 arg1);
void EftMesh_SetColor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_001EC460(s32 arg0);

/* 0x0019CB18: updates the colour of the mesh at arg0+0x38 (sub-block +0xAB0) from four float
 * channels at +0xBC0, +0xBC4, +0xBC8, +0xBCC (each clamped to a byte) and then either returns 4
 * when the flag halfword +0xC24 has bit 2 set, or tail-calls func_001EC460. */
s32 func_0019CB18(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 0x38);
    u8 *s1 = s0 + 0xAB0;
    u32 r;
    u32 g;
    u32 b;
    u32 a;

    func_001EC368((s32)s1, 1);

    r = CONV_U8(*(f32 *)(s0 + 0xBC0));
    g = CONV_U8(*(f32 *)(s0 + 0xBC4));
    b = CONV_U8(*(f32 *)(s0 + 0xBC8));
    a = CONV_U8(*(f32 *)(s0 + 0xBCC));
    EftMesh_SetColor((s32)s1, r, g, b, a);

    if ((*(u16 *)(s0 + 0xC24) & 4) != 0) {
        return 4;
    }
    return func_001EC460((s32)s1);
}
