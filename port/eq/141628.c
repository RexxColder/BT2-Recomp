#include "common.h"
void bt2_fightlog_note(const char *fmt, ...); /* TEMP TEX0 */

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

extern u8 *func_0012B9B0(void);
extern s32 func_00129720(u8 *dst, u8 *src, u8 *plane, s32 n);
extern void func_00129A50(u8 *a, u8 *b, u8 *pts, s32 n);
extern s32 func_001420F0(void);

/* cvt.w.s with the 2^31 fix-up */
#define f2u(f) ((f) >= 2147483648.0f ? ((s32)((f) - 2147483648.0f) | (s32)0x80000000) : (s32)(f))

/* Clips polygon pts (0x30-byte vertices) against 5 planes, projects it, and queues each fan triangle as one
   0x80-byte GIF packet (texture word tex) in the ordering table; layer selects the slot parity. The depth key is
   the mean screen z >> 8, pushed +-500 depending on func_001420F0. */
void func_00141628(u8 *pts, s32 layer, u64 tex) {
    u8 sp[0x180];   /* tamano de locales del original (antes 0x130) */
    u8 *plane;
    s32 cnt;
    s32 i;
    s32 k;
    u8 *q;
    u8 *r;
    u8 *v2p;
    u8 *vA;
    u8 *vB;
    u8 *pkt;
    u8 *slot;
    s32 key;
    s32 ok;
    s32 z;

    plane = func_0012B9B0();
    cnt = 3;
    for (i = 4; i >= 0; i--) {
        cnt = func_00129720(pts, pts, plane, cnt);
        plane += 16;
    }
    if (cnt == 0) {
        return;
    }
    func_00129A50(sp, sp + 0x90, pts, cnt);

    q = pts + 0x60;
    r = sp + 0xA0;
    for (k = 2; k < cnt; k++, q += 0x30, r += 0x10) {
        vA = sp + k * 16 - 16;
        vB = sp + k * 16;
        key = (*(s32 *)(sp + 8) + *(s32 *)(vA + 8) + *(s32 *)(vB + 8)) / 3 >> 8;
        if (func_001420F0()) {
            key = key - 500;
        } else {
            key = key + 500;
        }
        z = *(s32 *)(sp + 8);
        if (z > 0xFFFFFF) {
            *(s32 *)(sp + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vA + 8) > 0xFFFFFF) {
            *(s32 *)(vA + 8) = 0xFFFFFF;
        }
        if (*(s32 *)(vB + 8) > 0xFFFFFF) {
            *(s32 *)(vB + 8) = 0xFFFFFF;
        }
        ok = 1;
        if (*(s32 *)(sp + 8) > 0 && *(s32 *)(sp + 0) <= 0xFFEF && *(s32 *)(sp + 0) > 0 && *(s32 *)(sp + 4) <= 0xFFEF) {
            ok = *(s32 *)(sp + 4) < 1;
        }
        if (!ok) {
            ok = 1;
            if (*(s32 *)(vA + 8) > 0 && *(s32 *)(vA + 0) <= 0xFFEF && *(s32 *)(vA + 0) > 0 && *(s32 *)(vA + 4) <= 0xFFEF) {
                ok = *(s32 *)(vA + 4) < 1;
            }
            if (!ok) {
                ok = 1;
                if (*(s32 *)(vB + 8) > 0 && *(s32 *)(vB + 0) <= 0xFFEF && *(s32 *)(vB + 0) > 0 && *(s32 *)(vB + 4) <= 0xFFEF) {
                    ok = *(s32 *)(vB + 4) < 1;
                }
            }
        }
        if (ok) {
            continue;
        }
        pkt = D_00387AD8;
        D_00387AD8 = pkt + 0x80;
        *(u64 *)(pkt + 0x00) = 0xA0000007ull;
        *(u64 *)(pkt + 0x10) = 0xC400000000008001ull;
        *(u64 *)(pkt + 0x18) = 0xF42142142160ull;
        *(u64 *)(pkt + 0x20) = 0x5B;
        pkt[0x30] = f2u(*(f32 *)(pts + 0x20));
        pkt[0x31] = f2u(*(f32 *)(pts + 0x24));
        pkt[0x32] = f2u(*(f32 *)(pts + 0x28));
        pkt[0x33] = f2u(*(f32 *)(pts + 0x2C));
        *(f32 *)(pkt + 0x34) = *(f32 *)(sp + 0x98);
        pkt[0x48] = f2u(*(f32 *)(q - 0x10));
        pkt[0x49] = f2u(*(f32 *)(q - 0x0C));
        pkt[0x4A] = f2u(*(f32 *)(q - 0x08));
        pkt[0x4B] = f2u(*(f32 *)(q - 0x04));
        *(f32 *)(pkt + 0x4C) = *(f32 *)(r + 8);
        pkt[0x60] = f2u(*(f32 *)(q + 0x20));
        pkt[0x61] = f2u(*(f32 *)(q + 0x24));
        pkt[0x62] = f2u(*(f32 *)(q + 0x28));
        pkt[0x63] = f2u(*(f32 *)(q + 0x2C));
        *(f32 *)(pkt + 0x64) = *(f32 *)(sp + 0x98 + k * 16);
        *(u64 *)(pkt + 0x28) = tex;
        if ((u32)(*(u64 *)(pkt + 0x28) >> 32) == 0 && (u32)*(u64 *)(pkt + 0x28) > 0xFFFFu) bt2_fightlog_note("TEX0TRUNC 141628 %llx", (unsigned long long)*(u64 *)(pkt + 0x28)); /* TEMP TEX0 */
        *(f32 *)(pkt + 0x38) = *(f32 *)(sp + 0x90);
        *(f32 *)(pkt + 0x3C) = *(f32 *)(sp + 0x94);
        *(f32 *)(pkt + 0x50) = *(f32 *)(r + 0);
        *(f32 *)(pkt + 0x54) = *(f32 *)(r + 4);
        *(f32 *)(pkt + 0x68) = *(f32 *)(sp + 0x90 + k * 16);
        *(f32 *)(pkt + 0x6C) = *(f32 *)(sp + 0x94 + k * 16);
        *(u16 *)(pkt + 0x40) = *(u16 *)(sp + 0);
        *(u16 *)(pkt + 0x42) = *(u16 *)(sp + 4);
        *(u64 *)(pkt + 0x40) = (*(u64 *)(pkt + 0x40) & 0xFF000000FFFFFFFFull) | ((u64)(*(u32 *)(sp + 8) & 0xFFFFFF) << 32);
        pkt[0x47] = 0xFF;
        *(u16 *)(pkt + 0x58) = *(u16 *)(vA + 0);
        *(u16 *)(pkt + 0x5A) = *(u16 *)(vA + 4);
        *(u64 *)(pkt + 0x58) = (*(u64 *)(pkt + 0x58) & 0xFF000000FFFFFFFFull) | ((u64)(*(u32 *)(vA + 8) & 0xFFFFFF) << 32);
        pkt[0x5F] = 0xFF;
        *(u16 *)(pkt + 0x70) = *(u16 *)(vB + 0);
        *(u16 *)(pkt + 0x72) = *(u16 *)(vB + 4);
        *(u64 *)(pkt + 0x70) = (*(u64 *)(pkt + 0x70) & 0xFF000000FFFFFFFFull) | ((u64)(*(u32 *)(vB + 8) & 0xFFFFFF) << 32);
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
