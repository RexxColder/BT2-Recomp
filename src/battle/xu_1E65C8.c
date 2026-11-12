#include "common.h"
#include "m2c_macros.h"

extern f32 D_003434A8[] __attribute__((section(".data")));

/* Fills the 4-float record at arg0 from the 16-byte entry at arg1 + (arg2 & 0xFF) * 16: two 4-bit fields index the
   f32 table D_003434A8 (fields at bits 26 and 30 of the first word), +0xC is 1.0f, +8 is 0. */
void func_001E65C8(void *arg0, s32 arg1, s32 arg2) {
    u64 *e = (u64 *)(arg1 + ((arg2 & 0xFF) << 4));
    f32 one = M2C_BITWISE(f32, 0x3F800000);
    f32 a;
    f32 b;

    a = D_003434A8[(*e >> 26) & 0xF];
    *(f32 *)((u8 *)arg0 + 0) = a;
    b = D_003434A8[(*e >> 30) & 0xF];
    *(f32 *)((u8 *)arg0 + 0xC) = one;
    *(f32 *)((u8 *)arg0 + 4) = b;
    *(s32 *)((u8 *)arg0 + 8) = 0;
}
