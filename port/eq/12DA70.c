#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

/* 0x0012DA70: queues one gouraud-textured triangle as GIF packets (optional 0x30-byte setup packets before and
 * after a 0x80-byte primitive packet) and links them into the draw list slot chosen by idx / off. Skipped when
 * all three vertex alphas are <= D_00384180. */
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_00384180;

/* float -> u32 style truncation used for the colour bytes (cvt.w.s with the 2^31 fix-up) */
static s32 f2u(f32 f) {
    if (f >= 2147483648.0f) {
        return (s32)(f - 2147483648.0f) | (s32)0x80000000;
    }
    return (s32)f;
}

/* append pkt to the list slot: off < 0 -> slot idx, 0 <= off < 0x1000 -> slot idx + 2*off, else slot idx + 0xFFF0 bytes */
static void link_pkt(u8 *pkt, s32 idx, s32 off) {
    u8 *slot;
    u8 *tail;

    if (off < 0) {
        slot = D_00387AE0 + idx * 8;
    } else if (off >= 0x1000) {
        slot = D_00387AE0 + idx * 8 + 0xFFF0;
    } else {
        slot = D_00387AE0 + (off * 2 + idx) * 8;
    }
    tail = *(u8 **)(slot + 4);
    *(u8 **)(tail + 4) = pkt;
    *(u8 **)(slot + 4) = pkt;
}

void func_0012DA70(u8 *p0, u8 *p1, u8 *p2, f32 *cA, f32 *cB, f32 *cC, f32 *uvA, f32 *uvB, f32 *uvC,
                   u8 flagPre, u8 flagPost, s32 idx, s32 off, u64 tag) {
    s32 fanFlag = 1;
    u8 *q;

    if (!(cA[3] > D_00384180 || cB[3] > D_00384180 || cC[3] > D_00384180)) {
        return;
    }
    if (idx < 0) {
        idx = 0;
        fanFlag = 0;
    }

    if (flagPre) {
        q = D_00387AD8;
        D_00387AD8 = q + 0x30;
        *(u64 *)(q + 0x00) = 0xA0000002ull;
        *(u64 *)(q + 0x10) = 0x1000000000008001ull;
        *(u64 *)(q + 0x18) = 0xE;
        *(u64 *)(q + 0x20) = 0;
        *(u64 *)(q + 0x28) = 8;
        link_pkt(q, idx, off);
    }
    if (flagPost) {
        q = D_00387AD8;
        D_00387AD8 = q + 0x30;
        *(u64 *)(q + 0x00) = 0xA0000002ull;
        *(u64 *)(q + 0x10) = 0x1000000000008001ull;
        *(u64 *)(q + 0x20) = 0x310000E0ull;
        *(u64 *)(q + 0x18) = 0xE;
        *(u64 *)(q + 0x28) = 0x4E;
        link_pkt(q, idx, off);
    }

    q = D_00387AD8;
    D_00387AD8 = q + 0x80;
    *(u64 *)(q + 0x20) = (u64)((fanFlag << 6) | 0x1B);
    *(u64 *)(q + 0x10) = 0xC400000000008001ull;
    *(u64 *)(q + 0x00) = 0xA0000007ull;
    *(u64 *)(q + 0x18) = 0xF42142142160ull;

    q[0x30] = (u8)f2u(cA[0]);
    q[0x31] = (u8)f2u(cA[1]);
    q[0x32] = (u8)f2u(cA[2]);
    q[0x33] = (u8)f2u(cA[3]);
    *(f32 *)(q + 0x34) = uvA[2];
    q[0x48] = (u8)f2u(cB[0]);
    q[0x49] = (u8)f2u(cB[1]);
    q[0x4A] = (u8)f2u(cB[2]);
    q[0x4B] = (u8)f2u(cB[3]);
    *(f32 *)(q + 0x4C) = uvB[2];
    q[0x60] = (u8)f2u(cC[0]);
    q[0x61] = (u8)f2u(cC[1]);
    q[0x62] = (u8)f2u(cC[2]);
    q[0x63] = (u8)f2u(cC[3]);
    *(f32 *)(q + 0x64) = uvC[2];
    *(u64 *)(q + 0x28) = tag;
    if ((u32)(tag >> 32) == 0 && (u32)tag > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 12DA70 %llx ret %p", (unsigned long long)tag, __builtin_return_address(0)); /* TEMP TEX0 */
    *(f32 *)(q + 0x38) = uvA[0];
    *(f32 *)(q + 0x3C) = uvA[1];
    *(f32 *)(q + 0x50) = uvB[0];
    *(f32 *)(q + 0x54) = uvB[1];
    *(f32 *)(q + 0x68) = uvC[0];
    *(f32 *)(q + 0x6C) = uvC[1];

    *(u16 *)(q + 0x40) = *(u16 *)p0;
    *(u16 *)(q + 0x42) = *(u16 *)(p0 + 4);
    *(u32 *)(q + 0x44) = (*(u32 *)(q + 0x44) & 0xFF000000u) | (*(u32 *)(p0 + 8) & 0xFFFFFFu);
    q[0x47] = 0xFF;
    *(u16 *)(q + 0x58) = *(u16 *)p1;
    *(u16 *)(q + 0x5A) = *(u16 *)(p1 + 4);
    *(u32 *)(q + 0x5C) = (*(u32 *)(q + 0x5C) & 0xFF000000u) | (*(u32 *)(p1 + 8) & 0xFFFFFFu);
    q[0x5F] = 0xFF;
    *(u16 *)(q + 0x70) = *(u16 *)p2;
    *(u16 *)(q + 0x72) = *(u16 *)(p2 + 4);
    *(u32 *)(q + 0x74) = (*(u32 *)(q + 0x74) & 0xFF000000u) | (*(u32 *)(p2 + 8) & 0xFFFFFFu);
    q[0x77] = 0xFF;
    link_pkt(q, idx, off);

    if (flagPost) {
        q = D_00387AD8;
        D_00387AD8 = q + 0x30;
        *(u64 *)(q + 0x00) = 0xA0000002ull;
        *(u64 *)(q + 0x10) = 0x1000000000008001ull;
        *(u64 *)(q + 0x18) = 0xE;
        *(u64 *)(q + 0x28) = 0x4E;
        *(u64 *)(q + 0x20) = 0x1310000E0ull;
        link_pkt(q, idx, off);
    }
}
