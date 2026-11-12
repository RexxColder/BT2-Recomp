#include "m2c_macros.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

/* GS sprite packet builder: 0x60 bytes taken from the bump pointer D_00387AD8, linked into D_00387AE4. */
void func_001EF4F8(s32 r, s32 g, s32 b, s32 a, s32 p4, s32 p5, s32 p6, s32 p7,
                   s32 s8, s32 s9, s32 s10, s32 s11, s32 s12, s32 s13, s32 s14, u8 *s15) {
    u8 *t4;
    u8 *slot;
    u8 *old;
    s64 t3;
    s64 t5;
    s32 sx13;
    s32 v3;
    u64 v0;

    t4 = D_00387AD8;
    D_00387AD8 = t4 + 0x60;

    sx13 = (s32)(signed char)s13;
    v3 = sx13 * 16;
    t5 = (s64)sx13 << 9;

    *(u8 *)(t4 + 0x30) = (u8)r;
    *(u8 *)(t4 + 0x31) = (u8)g;
    *(u8 *)(t4 + 0x32) = (u8)b;
    *(u8 *)(t4 + 0x33) = (u8)a;
    *(f32 *)(t4 + 0x34) = 1.0f;
    *(u16 *)(t4 + 0x38) = (u16)(s9 * 16);
    *(u16 *)(t4 + 0x3A) = (u16)(s10 * 16);
    *(u16 *)(t4 + 0x40) = (u16)(p4 * 16 + 0x7000);
    *(u16 *)(t4 + 0x42) = (u16)(p5 * 16 + 0x7200);
    *(u16 *)(t4 + 0x48) = (u16)((s9 + s11) * 16);
    *(u16 *)(t4 + 0x4A) = (u16)((s10 + s12) * 16);
    *(u16 *)(t4 + 0x50) = (u16)((p4 + p7) * 16 + 0x7000);
    *(u16 *)(t4 + 0x52) = (u16)((p5 + s8) * 16 + 0x7200);
    *(u8 *)(t4 + 0x47) = 0xFF;
    *(u8 *)(t4 + 0x57) = 0xFF;

    v0 = *(u64 *)(t4 + 0x40);
    v0 = v0 | 0x00FFFFFF00000000ULL;
    *(u64 *)(t4 + 0x40) = v0;

    v0 = *(u64 *)(t4 + 0x50);
    v0 = v0 | 0x00FFFFFF00000000ULL;
    *(u64 *)(t4 + 0x50) = v0;

    *(u64 *)(t4 + 0x0) = 0xA0000005ULL;
    *(u64 *)(t4 + 0x10) = 0x8400000000008001ULL;
    t3 = (s64)v3 + 0xF4343160LL;
    *(s64 *)(t4 + 0x18) = t3;
    t5 = t5 | 0x40 | 0x116;
    *(s64 *)(t4 + 0x20) = t5;
    *(u64 *)(t4 + 0x28) = *(u64 *)s15;

    /* link fields are 32-bit words (lw/sw) in the asm */
    slot = D_00387AE4 + (2 * p6 + s14) * 8;
    old = (u8 *)(unsigned long)*(u32 *)(slot + 4);
    *(u32 *)(old + 4) = (u32)(unsigned long)t4;
    *(u32 *)(slot + 4) = (u32)(unsigned long)t4;
}
