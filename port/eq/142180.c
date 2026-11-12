#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

/* GS packet builder, 0x80 bytes taken from the bump pointer D_00387AD8: a textured triangle with three vertices
   (position bytes from vecA/vecB/vecC, uv words from uvA/uvB/uvC, 24-bit colors cA/cB/cC), then linked into the
   ordering table D_00387AE0 at slot ot (+ depth*2 when 0 <= depth < 0x1000, clamped past the end otherwise). */
s32 func_00142180(u8 *cA, u8 *cB, u8 *cC, f32 *vecA, f32 *vecB, f32 *vecC, u8 *uvA, u8 *uvB, u8 *uvC, s32 ot,
                  s32 depth, s64 tag) {
    u8 *pkt = D_00387AD8;
    u8 *link;
    u8 *prev;
    u64 q;

    D_00387AD8 = pkt + 0x80;
    *(s64 *)(pkt + 0x20) = 0x5B;
    *(s64 *)(pkt + 0x00) = 0xA0000007;
    *(s64 *)(pkt + 0x10) = (s64)0xC400000000008001ULL;
    *(s64 *)(pkt + 0x18) = 0xF42142142160LL;
    pkt[0x30] = (u8)(u32)vecA[0];
    pkt[0x31] = (u8)(u32)vecA[1];
    pkt[0x32] = (u8)(u32)vecA[2];
    pkt[0x33] = (u8)(u32)vecA[3];
    *(u32 *)(pkt + 0x34) = *(u32 *)(uvA + 8);
    pkt[0x48] = (u8)(u32)vecB[0];
    pkt[0x49] = (u8)(u32)vecB[1];
    pkt[0x4A] = (u8)(u32)vecB[2];
    pkt[0x4B] = (u8)(u32)vecB[3];
    *(u32 *)(pkt + 0x4C) = *(u32 *)(uvB + 8);
    pkt[0x60] = (u8)(u32)vecC[0];
    pkt[0x61] = (u8)(u32)vecC[1];
    pkt[0x62] = (u8)(u32)vecC[2];
    pkt[0x63] = (u8)(u32)vecC[3];
    *(u32 *)(pkt + 0x64) = *(u32 *)(uvC + 8);
    *(s64 *)(pkt + 0x28) = tag;
    if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 142180 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
    *(u32 *)(pkt + 0x38) = *(u32 *)(uvA + 0);
    *(u32 *)(pkt + 0x3C) = *(u32 *)(uvA + 4);
    *(u32 *)(pkt + 0x50) = *(u32 *)(uvB + 0);
    *(u32 *)(pkt + 0x54) = *(u32 *)(uvB + 4);
    *(u32 *)(pkt + 0x68) = *(u32 *)(uvC + 0);
    *(u32 *)(pkt + 0x6C) = *(u32 *)(uvC + 4);

    *(u16 *)(pkt + 0x40) = *(u16 *)(cA + 0);
    *(u16 *)(pkt + 0x42) = *(u16 *)(cA + 4);
    q = *(u64 *)(pkt + 0x40);
    q = (q & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(cA + 8) & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x40) = q;
    pkt[0x47] = 0xFF;

    *(u16 *)(pkt + 0x58) = *(u16 *)(cB + 0);
    *(u16 *)(pkt + 0x5A) = *(u16 *)(cB + 4);
    q = *(u64 *)(pkt + 0x58);
    q = (q & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(cB + 8) & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x58) = q;
    pkt[0x5F] = 0xFF;

    *(u16 *)(pkt + 0x70) = *(u16 *)(cC + 0);
    *(u16 *)(pkt + 0x72) = *(u16 *)(cC + 4);
    q = *(u64 *)(pkt + 0x70);
    q = (q & 0xFF000000FFFFFFFFULL) | ((u64)(*(u32 *)(cC + 8) & 0xFFFFFF) << 32);
    *(u64 *)(pkt + 0x70) = q;
    pkt[0x77] = 0xFF;

    if (depth < 0) {
        link = D_00387AE0 + (ot << 3);
        prev = *(u8 **)(link + 4);
    } else if (depth < 0x1000) {
        link = D_00387AE0 + ((depth * 2 + ot) << 3);
        prev = *(u8 **)(link + 4);
    } else {
        link = D_00387AE0 + (ot << 3) + 0xFFF0;
        prev = *(u8 **)(link + 4);
    }
    *(u8 **)(prev + 4) = pkt;
    *(u8 **)(link + 4) = pkt;
    return (s32)prev;
}
