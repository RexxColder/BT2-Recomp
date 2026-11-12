#include "m2c_macros.h"

extern u8 *D_00387B00;
extern u8 gStgTintColor0[] __attribute__((section(".data")));

void Dma_AddZbuf(s32 a0, s32 a1);
void StgTint_CalcColor(u8 *obj);
void func_00281CF8(s32 a0, u8 *obj);

/* float -> u32 bits as the asm does it: trunc, with the 2^31 split for large values */
#define TINT_F2I(f) (((f) >= 2147483648.0f) ? ((s32)((f) - 2147483648.0f) | (s32)0x80000000u) : (s32)(f))

void func_002820C8(void) {
    u8 *s0;

    Dma_AddZbuf(0xE0, 1);
    s0 = D_00387B00;
    if (*(u8 *)(s0 + 0x58) & 1) {
        StgTint_CalcColor(s0);
        func_00281CF8(0x44, s0);
        *(s32 *)(gStgTintColor0 + 0x0) = TINT_F2I(*(f32 *)(s0 + 0x0));
        *(s32 *)(gStgTintColor0 + 0x4) = TINT_F2I(*(f32 *)(s0 + 0x4));
        *(s32 *)(gStgTintColor0 + 0x8) = TINT_F2I(*(f32 *)(s0 + 0x8));
        *(s32 *)(gStgTintColor0 + 0xC) = TINT_F2I(*(f32 *)(s0 + 0xC));
    } else {
        *(s32 *)(gStgTintColor0 + 0xC) = 0;
        *(s32 *)(gStgTintColor0 + 0x0) = 0;
        *(s32 *)(gStgTintColor0 + 0x4) = 0;
        *(s32 *)(gStgTintColor0 + 0x8) = 0;
    }
    s0 = D_00387B00 + 0x60;
    if (*(u8 *)(s0 + 0x58) & 1) {
        StgTint_CalcColor(s0);
        func_00281CF8(0x44, s0);
    }
    Dma_AddZbuf(0xE0, 0);
}
