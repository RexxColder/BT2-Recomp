#include "m2c_macros.h"

s32 func_0010B0A0();
s64 Tex_Log2Size(s32);
void Dma_AddTexFlush(void);
void func_0010C650(s64);
void func_00112BB8(s32, s32);

// Sets up a 128x128 texture descriptor from its two log2 sizes (packed into a 64-bit GS word with the 0x9C00 field), then runs the texture DMA steps.
void func_00116CE0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    s32 temp_s1;
    s64 temp_s0;
    s64 packed;

    temp_s1 = func_0010B0A0(r_a0);
    temp_s0 = Tex_Log2Size(0x80);
    packed = (temp_s0 << 0x1A) | (Tex_Log2Size(0x80) << 0x1E);
    func_0010C650(packed | ((s64) 8 << 32 | 0x9C00));
    func_00112BB8(temp_s1 + 0x38A0, 1);
    Dma_AddTexFlush();
}
