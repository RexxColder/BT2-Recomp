#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *gEftSurf;
extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern f32 D_003842E8;

extern s32 func_00129720(u8 *dst, u8 *src, u8 *plane, s32 n);
extern void func_00129A50(u8 *a, u8 *b, u8 *pts, s32 n);
extern void func_00129C28(u8 *dst, u8 *src);

/* float -> u32 style truncation (cvt.w.s with the 2^31 fix-up) */
#define f2u(f) ((f) >= 2147483648.0f ? ((s32)((f) - 2147483648.0f) | (s32)0x80000000) : (s32)(f))

/* Clips the polygon `pts` (vertex vectors of 0x30 bytes: position, colour, uv) against the five planes of
   gEftSurf+0x10, then for each fan triangle (vertex 0, k-1, k) queues one or two 0x80-byte GIF packets
   (two when any vertex alpha in `cols` is above D_003842E8) into the ordering table. `texs` holds one
   8-byte texture word per packet, `cols` the per-vertex alpha floats (stride 4 floats at +0xC), `bias`
   is subtracted from the depth key. */
void func_00138C90(u8 *pts, s32 unused, u64 *texs, f32 *cols, s32 bias) {
    u8 sp[0x1A0];
    u8 *plane;
    s32 cnt;
    s32 i, k;
    u8 *base;
    u8 *v1p;
    u8 *v2p;
    u8 *q;
    u8 *r;
    u8 *pkt;
    u8 *slot;
    s32 key;
    s32 n;
    s32 layer;
    s32 t;
    f32 *cv;
    u64 *tp;

    plane = *(u8 **)(gEftSurf + 0x10);
    *(s32 *)(sp + 0x188) = 3;
    for (i = 4; i >= 0; i--) {
        cnt = func_00129720(pts, pts, plane, *(s32 *)(sp + 0x188));
        *(s32 *)(sp + 0x188) = cnt;
        plane += 16;
    }
    if (cnt == 0) {
        return;
    }
    func_00129A50(sp, sp + 0x90, pts, cnt);

    base = pts + 0x20;
    q = pts + 0x60;
    r = sp + 0xA0;
    v2p = sp + 0x20;
    for (k = 2; k < *(s32 *)(sp + 0x188); k++, q += 0x30, r += 0x10, v2p += 0x10) {
        v1p = q - 0x10;
        key = (*(s32 *)(sp + 8) >> 8) - bias;
        n = 2;
        if (*(f32 *)(base + 0xC) <= 0.0f && *(f32 *)(q - 4) <= 0.0f && *(f32 *)(q + 0x2C) <= 0.0f) {
            continue;
        }
        if (cols[3] <= D_003842E8 && cols[7] <= D_003842E8 && cols[11] <= D_003842E8) {
            n = 1;
        }
        layer = 0;
        func_00129C28(sp + 0x120, base);
        func_00129C28(sp + 0x130, v1p);
        func_00129C28(sp + 0x140, q + 0x20);
        func_00129C28(sp + 0x150, base);
        func_00129C28(sp + 0x160, v1p);
        func_00129C28(sp + 0x170, q + 0x20);
        *(f32 *)(sp + 0x15C) = *(f32 *)(sp + 0x15C) * cols[3];
        *(f32 *)(sp + 0x16C) = *(f32 *)(sp + 0x16C) * cols[7];
        *(f32 *)(sp + 0x17C) = *(f32 *)(sp + 0x17C) * cols[11];
        cv = (f32 *)(sp + 0x120);
        tp = texs;
        for (t = 0; t < n; t++, cv += 12, tp++, layer++) {
            pkt = D_00387AD8;
            D_00387AD8 = pkt + 0x80;
            *(u64 *)(pkt + 0x00) = 0xA0000007ull;
            *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
            *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
            *(u64 *)(pkt + 0x20) = 0x5B;
            pkt[0x30] = f2u(cv[0]);
            pkt[0x31] = f2u(cv[1]);
            pkt[0x32] = f2u(cv[2]);
            pkt[0x33] = f2u(cv[3]);
            *(f32 *)(pkt + 0x34) = *(f32 *)(sp + 0x98);
            pkt[0x48] = f2u(cv[4]);
            pkt[0x49] = f2u(cv[5]);
            pkt[0x4A] = f2u(cv[6]);
            pkt[0x4B] = f2u(cv[7]);
            *(f32 *)(pkt + 0x4C) = *(f32 *)(r + 8);
            pkt[0x60] = f2u(cv[8]);
            pkt[0x61] = f2u(cv[9]);
            pkt[0x62] = f2u(cv[10]);
            pkt[0x63] = f2u(cv[11]);
            *(f32 *)(pkt + 0x64) = *(f32 *)(v2p + 0x98);
            *(u64 *)(pkt + 0x28) = *tp;
            if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 138C90 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
            *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0x90);
            *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0x94);
            *(f32 *)(pkt + 0x50) = *(f32 *)(r + 0);
            *(f32 *)(pkt + 0x54) = *(f32 *)(r + 4);
            *(f32 *)(pkt + 0x68) = *(f32 *)(v2p + 0x90);
            *(f32 *)(pkt + 0x6C) = *(f32 *)(v2p + 0x94);
            *(u16 *)(pkt + 0x40) = *(u16 *)(sp + 0);
            *(u16 *)(pkt + 0x42) = *(u16 *)(sp + 4);
            *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFull) |
                                   ((u64)(*(u32 *)(sp + 8) & 0xFFFFFF) << 32);
            pkt[0x47] = 0xFF;
            *(u16 *)(pkt + 0x58) = *(u16 *)(v2p - 0x10);
            *(u16 *)(pkt + 0x5A) = *(u16 *)(v2p - 0xC);
            *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & 0xFF000000FFFFFFFFull) |
                                   ((u64)(*(u32 *)(v2p - 8) & 0xFFFFFF) << 32);
            pkt[0x5F] = 0xFF;
            *(u16 *)(pkt + 0x70) = *(u16 *)(v2p + 0);
            *(u16 *)(pkt + 0x72) = *(u16 *)(v2p + 4);
            *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFull) |
                                   ((u64)(*(u32 *)(v2p + 8) & 0xFFFFFF) << 32);
            pkt[0x77] = 0xFF;
            if (key < 0) {
                slot = D_00387AE0 + layer * 8;
            } else if (key < 0x1000) {
                slot = D_00387AE0 + (key * 2 + layer) * 8;
            } else {
                slot = D_00387AE0 + layer * 8 + 0xFFF0;
            }
            *(u8 **)(*(u8 **)(slot + 4) + 4) = pkt;
            *(u8 **)(slot + 4) = pkt;
        }
    }
}
