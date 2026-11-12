#include "common.h"

extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern u8 *func_002768D8(s32 arg0);
extern void GfxWater_SetColor(s32 idx, s32 r, s32 g, s32 b, s32 a);
extern u8 *Dma_BeginDirect(void);
extern void Dma_EndDirect(u8 *end);
extern u8 *D_003876A0;
extern u8 *D_00387B0C;
extern s32 D_00387B10;
extern u8 gGfx[];
extern f32 D_003870D8, D_003870DC, D_003870E0, D_003870E4, D_003870E8;

#define Q(a, b) \
    do { \
        ((u64 *)p)[0] = (u64)(a); \
        ((u64 *)p)[1] = (u64)(b); \
        p += 16; \
    } while (0)

/* Draws the water-ripple grid for slot idx: advances the scroll offsets, warps a grid of vertices with cos
   waves around the centre, then emits the GS packet (sprite strips + textured triangle strips). */
void func_00285028(u8 sel, s32 idx) {
    s32 A[60];
    s32 B[60];
    s32 W, H, U0, V1, n;
    s32 rowOff;
    s32 row, col;
    s32 off;
    u8 *p;
    u8 *hdr;
    u8 *tab;

    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x2000) {
        return;
    }
    hdr = func_002768D8(7);
    GfxWater_SetColor(idx, hdr[1], hdr[2], hdr[3], hdr[4]);
    if (!(*(u64 *)(D_003876A0 + 0x4D8) & 0x100)) {
        u8 *e;

        off = idx * 4;
        e = D_00387B0C + (off + idx) * 4;
        *(f32 *)e = *(f32 *)e + *(f32 *)(e + 8);
        e = D_00387B0C + (off + idx) * 4;
        if (D_003870D8 < *(f32 *)e) {
            *(f32 *)e = *(f32 *)e - D_003870DC;
        }
        e = D_00387B0C + (off + idx) * 4;
        *(f32 *)(e + 4) = *(f32 *)(e + 4) + *(f32 *)(e + 12);
        e = D_00387B0C + (off + idx) * 4;
        if (D_003870D8 < *(f32 *)(e + 4)) {
            *(f32 *)(e + 4) = *(f32 *)(e + 4) - D_003870E0;
        }
    } else {
        off = idx << 2;
    }
    if (sel != 0) {
        W = 0x100;
        H = 0x100;
        n = 5;
        if (idx == 0) {
            U0 = 0;
            V1 = 0x100;
        } else {
            U0 = 0x100;
            V1 = 0x200;
        }
    } else {
        W = 0x200;
        H = 0x200;
        U0 = 0;
        V1 = 0x200;
        n = 10;
    }

    rowOff = 0;
    for (row = 0; row < 6; row++) {
        if (n != 0) {
            f32 fH = (f32)H;
            f32 fV = (f32)D_00387B10;
            f32 k1 = D_003870E4;
            f32 k2 = D_003870E8;
            s32 *a = &A[row * 10];
            s32 *b = &B[row * 10];
            s32 fp = 0;
            s32 remain;

            for (remain = n; remain != 0; remain--, a++, b++, fp += H) {
                s32 ix = fp / (n - 1);
                s32 iy = rowOff / 5;
                f32 fx = (f32)ix, fy = (f32)iy;
                f32 dx, dy, dist, d2, mag;

                *a = ix << 4;
                *b = iy << 4;
                dx = fx - fH * k1;
                dy = fy - fV * k1;
                dist = __builtin_sqrtf(dx * dx + dy * dy);
                tab = D_00387B0C;
                d2 = dist * k1;
                *a = *a + (s32)(((cosf(*(f32 *)(tab + idx * 20) + d2) * (dx / dist)) * 3.0f) * 16.0f);
                {
                    f32 dy0 = dy;
                    f32 dist0 = dist;

                    dx = fx - fH * k2;
                    dy = fy - fV * k2;
                    tab = D_00387B0C;
                    *b = *b + (s32)(((cosf(*(f32 *)(tab + idx * 20) + d2) * (dy0 / dist0)) * 3.0f) * 16.0f);
                }
                dist = __builtin_sqrtf(dx * dx + dy * dy);
                d2 = dist * k1;
                tab = D_00387B0C;
                *a = *a + (s32)(((cosf(*(f32 *)(tab + idx * 20 + 4) + d2) * (dx / dist)) * 3.0f) * 16.0f);
                tab = D_00387B0C;
                *b = *b + (s32)(((cosf(*(f32 *)(tab + idx * 20 + 4) + d2) * (dy / dist)) * 3.0f) * 16.0f);
                if (*a < 0) {
                    *a = 0;
                }
                if (H * 16 < *a) {
                    *a = H * 16;
                }
                if (*b < 0) {
                    *b = 0;
                }
                if (0xE00 < *b) {
                    *b = 0xE00;
                }
            }
        }
        rowOff += 0xE0;
    }

    p = Dma_BeginDirect();
    Q(0x1000000000000009ULL, 0xE);
    Q(0x30000, 0x47);
    Q(0, 0x4A);
    Q(0x60, 0x14);
    Q((*(u32 *)(gGfx + 0x234) & 1) ? 0x264020000ULL : 0x264020E00ULL, 6);
    Q(0x80150, 0x4C);
    Q(0x1310000E0ULL, 0x4E);
    Q((((u64)(H - 1)) << 16) | 0xDF000000000000ULL, 0x40);
    Q(((u64)U0 << 4) | 0x70000000000ULL | ((u64)V1 << 14) | 0xA, 8);
    Q(0x44, 0x42);
    Q(0x1000000000000002ULL, 0xE);
    Q(0x116, 0);
    Q(0x3F80000080808080ULL, 1);
    {
        u32 strips = (u32)W >> 5;
        s32 i;
        s32 step;

        Q(strips | 0x4400000000000000ULL, 0x5353);
        step = (H / (s32)strips) << 4;
        if (strips != 0) {
            s32 x = U0;
            s32 t0 = (U0 << 4) + 0x200;
            s32 a2 = step + 0x7000;
            s32 t3 = 0x7000;

            for (i = 0; i < (s32)strips; i++) {
                Q((u64)(x << 4), (u64)(u32)(t3 | 0x72000000));
                x += 0x20;
                t3 += step;
                Q((u64)(u32)(t0 | 0x1C000000), 0x80000000ULL | (u32)a2);
                t0 += 0x200;
                a2 += step;
            }
        }
    }
    Q(0x1000000000000004ULL, 0xE);
    Q(0x264022A00ULL, 6);
    Q((*(u32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070, 0x4C);
    Q(((u64)U0 | ((u64)(V1 - 1) << 16)) | 0x1BF000000000000ULL, 0x40);
    Q(((u64)H << 14) | 0x38000000000ULL | 0xA, 8);
    {
        s32 r;

        Q(0x2400000000000001ULL, 0x10);
        for (r = 0;;) {
            Q(0x114, *(u32 *)(D_00387B0C + (off + idx) * 4 + 0x10) | 0x3F80000000000000ULL);
            Q((u64)n | 0x4400000000000000ULL, 0x5353);
            if (n != 0) {
                s32 q = 0;
                s32 col2;
                s32 *a = &A[r * 10];
                s32 *b = &B[r * 10];

                for (col2 = n; col2 != 0; col2--, a++, b++) {
                    s32 iq = q / (n - 1);
                    s32 u = (U0 + iq) * 16 + 0x7000;

                    q += W;
                    Q((u32)a[0] | ((u64)(u32)b[0] << 16),
                      (u64)(u32)u | ((u64)(u32)((0x1C0 * r) / 5 * 16 + 0x7200) << 16));
                    Q((u32)a[10] | ((u64)(u32)b[10] << 16),
                      (u64)(u32)u | ((u64)(u32)((0x1C0 * (r + 1)) / 5 * 16 + 0x7200) << 16));
                }
            }
            r = r + 1;
            if (r >= 5) {
                break;
            }
            Q(0x2400000000000001ULL, 0x10);
        }
    }
    Q(0x1000000000008002ULL, 0xE);
    Q(0x310000E0, 0x4E);
    Q(0x1BF000001FF0000ULL, 0x40);
    Dma_EndDirect(p);
}
