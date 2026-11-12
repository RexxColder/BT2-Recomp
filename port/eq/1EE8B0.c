#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern f32 D_003856E4;

s32 Dma_BeginDirect(s32 arg0, s32 arg1);
void Dma_EndDirect(s32 arg0);

/* byte copy into the DMA buffer (optnone: no memcpy intrinsic on game memory) */
__attribute__((noinline, optnone)) static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

/* float -> u32 the way the compiler emitted it: values >= 2^31 are converted after subtracting 2^31 */
static u32 f32_to_u32(f32 x) {
    if (x >= 2147483648.0f) {
        return (u32)(s32)(x - 2147483648.0f) | 0x80000000;
    }
    return (u32)(s32)x;
}

/* Builds a 7-qword GIF packet (three colored vertices with their texcoords/positions) and sends it
   through the direct DMA buffer; skipped when every one of the three colors has w < D_003856E4. */
void func_001EE8B0(s16 *arg0, s16 *arg1, s16 *arg2, f32 *col0, f32 *col1, f32 *col2,
                   f32 *st0, f32 *st1, f32 *pos0, u64 tagWord, s8 flag) {
    u8 sp[0x90];   /* tamano de locales del original (antes 0x80) */
    s32 buf;

    if (!(col0[3] < D_003856E4) || !(col1[3] < D_003856E4) || !(col2[3] < D_003856E4)) {
        buf = Dma_BeginDirect((s32)arg0, (s32)arg1);

        *(u64 *)(sp + 0x20) = ((u64)(s64)flag << 6) | 0x1B;
        *(u64 *)(sp + 0x00) = 0xA0000007;
        *(u64 *)(sp + 0x10) = 0xC400000000008001ULL;
        *(u64 *)(sp + 0x18) = 0xF42142142160ULL;

        sp[0x30] = (u8)f32_to_u32(col0[0]);
        sp[0x31] = (u8)f32_to_u32(col0[1]);
        sp[0x32] = (u8)f32_to_u32(col0[2]);
        sp[0x33] = (u8)f32_to_u32(col0[3]);
        *(f32 *)(sp + 0x34) = st0[2];

        sp[0x48] = (u8)f32_to_u32(col1[0]);
        sp[0x49] = (u8)f32_to_u32(col1[1]);
        sp[0x4A] = (u8)f32_to_u32(col1[2]);
        sp[0x4B] = (u8)f32_to_u32(col1[3]);
        *(f32 *)(sp + 0x4C) = st1[2];

        sp[0x60] = (u8)f32_to_u32(col2[0]);
        sp[0x61] = (u8)f32_to_u32(col2[1]);
        sp[0x62] = (u8)f32_to_u32(col2[2]);
        sp[0x63] = (u8)f32_to_u32(col2[3]);

        *(s16 *)(sp + 0x42) = arg0[2];
        *(s16 *)(sp + 0x58) = arg1[0];
        *(s16 *)(sp + 0x40) = arg0[0];
        *(s16 *)(sp + 0x5A) = arg1[2];
        *(u32 *)(sp + 0x44) = (*(u32 *)((u8 *)arg0 + 8) & 0xFFFFFF) | 0xFF000000;
        *(u32 *)(sp + 0x5C) = (*(u32 *)((u8 *)arg1 + 8) & 0xFFFFFF) | 0xFF000000;

        *(f32 *)(sp + 0x64) = pos0[2];
        *(f32 *)(sp + 0x38) = st0[0];
        *(f32 *)(sp + 0x3C) = st0[1];
        *(f32 *)(sp + 0x50) = st1[0];
        *(f32 *)(sp + 0x54) = st1[1];
        *(f32 *)(sp + 0x68) = pos0[0];
        *(f32 *)(sp + 0x6C) = pos0[1];
        *(u64 *)(sp + 0x28) = tagWord;
        if ((u32)(*(u64 *)(sp + 0x28) >> 32) == 0 && (u32)*(u64 *)(sp + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 1EE8B0 %llx ret %p", (unsigned long long)*(u64 *)(sp + 0x28), __builtin_return_address(0)); /* TEMP TEX0 */

        *(s16 *)(sp + 0x70) = arg2[0];
        *(s16 *)(sp + 0x72) = arg2[2];
        *(u32 *)(sp + 0x74) = (*(u32 *)((u8 *)arg2 + 8) & 0xFFFFFF) | 0xFF000000;

        blob_copy((u8 *)buf, sp + 0x10, 7 << 4);
        Dma_EndDirect(buf + (7 << 4));
    }
}
