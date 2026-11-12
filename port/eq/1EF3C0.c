#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE4;

/* 0x001EF3C0: GS packet builder for a 0x40-byte sprite packet at the cursor D_00387AD8 (which
 * advances by 0x40 whether or not a packet is written). Bytes: arg0..arg2 and arg3 (low byte) at
 * +0x28..+0x2B, a word with (arg3 bit 7 clear) << 6 | sext(arg10) << 9 | 1 at +0x20, the header
 * 0xA0000003, 0x4400000000008001 and 0x4410, the float 1.0 at +0x2C, two halfword pairs at +0x30
 * and +0x38 (arg4/arg5 and arg6/arg7 scaled by 16 with offsets 0x7000/0x7200), 0xFF bytes at +0x37
 * and +0x3F. The packet is linked into the list entry at D_00387AE4 + 8*(2*arg8 + arg11). */
void func_001EF3C0(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s8 arg10, s32 arg11) {
    u8 *pk = D_00387AD8;
    u32 s0 = arg3 & 0xFF;
    u64 fl = ((s0 & 0x80) == 0) ? 1 : 0;
    u64 a1m = 0x00FFFFFF00000000ULL;
    u64 a0w;
    u64 v0;
    u64 v1;
    s32 t4;
    u8 *e;
    u8 *n;

    (void)arg9;
    D_00387AD8 = pk + 0x40;
    if (pk == NULL) {
        return;
    }

    t4 = ((arg8 * 2) + arg11) * 8;

    *(u16 *)(pk + 0x30) = (u16)((arg4 << 4) + 0x7000);
    *(u16 *)(pk + 0x32) = (u16)((arg5 << 4) + 0x7200);
    *(u16 *)(pk + 0x38) = (u16)((arg6 << 4) + 0x7000);
    *(u16 *)(pk + 0x3A) = (u16)((arg7 << 4) + 0x7200);

    a0w = 1 | (fl << 6) | (u64)((s64)arg10 * 512);

    v0 = *(u64 *)(pk + 0x30) | a1m;
    v1 = *(u64 *)(pk + 0x38) | a1m;
    *(u64 *)(pk + 0x30) = v0;
    *(u64 *)(pk + 0x38) = v1;

    *(u8 *)(pk + 0x28) = arg0;
    *(u8 *)(pk + 0x29) = arg1;
    *(u8 *)(pk + 0x2A) = arg2;
    *(u8 *)(pk + 0x2B) = (u8)s0;
    *(u64 *)(pk + 0x20) = a0w;
    *(u64 *)(pk + 0x00) = 0xA0000003ULL;
    *(u64 *)(pk + 0x10) = 0x4400000000008001ULL;
    *(u64 *)(pk + 0x18) = 0x4410;
    *(f32 *)(pk + 0x2C) = 1.0f;
    *(u8 *)(pk + 0x37) = 0xFF;
    *(u8 *)(pk + 0x3F) = 0xFF;

    e = D_00387AE4 + t4;
    n = *(u8 **)(e + 0x4);
    *(u8 **)(n + 0x4) = pk;
    *(u8 **)(e + 0x4) = pk;
}
