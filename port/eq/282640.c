#include "common.h"

#define SW(o) (*(s32 *)(sp + (o)))
#define SF(o) (*(f32 *)(sp + (o)))
#define W(x) (*p++ = (u64)(x))
#define Q(a, b) do { W(a); W(b); } while (0)
#define S64(x) ((u64)(s64)(s32)(x))

extern u8 gGfx[] __attribute__((section(".data")));
extern u8 D_002C3630[] __attribute__((section(".data")));
extern s32 D_00387B08;
extern u8 *D_00387B04;
extern u8 *D_003876A0;
extern u8 *gBtlCam;
extern u8 *gBtlCamView;

extern u64 *Dma_BeginDirect();
extern void Dma_EndDirect(u64 *arg0);
extern void func_003126C8(u8 *dst, u8 *src);
extern void sceVu0CopyMatrix(u8 *dst, u8 *src);
extern void sceVu0ApplyMatrix(u8 *dst, u8 *m, u8 *v);

/* 0x00282640: builds a GIF/DMA packet for one rectangle (a0 = layout flag, a1 = entry index);
 * entries of 48 bytes at D_00387B04. The packet is a linear stream of u64. */
void func_00282640(s32 flag, s32 idx) {
    u8 sp[0x2D0];
    u8 *tbl = D_00387B04;
    u8 *ent = tbl + idx * 48;
    u64 *p;
    s32 W_, H, X0, W2, base, i, n, a2, lo, a3, k;
    s32 s0, s3, s6, t6, t7;
    f32 f3, f2, f4, f0, f1;

    SW(0x210) = idx;
    SW(0x254) = idx * 2;
    if ((*(s32 *)(ent + 0x1C) & 0xFF000000) == 0) {
        if ((*(u64 *)(ent + 0x20) & 0xFF000000FF000000ULL) == 0) {
            return;
        }
    }
    flag &= 0xFF;
    if (flag != 0) {
        SW(0x230) = 0x100;
        H = 0x80;
        if (idx == 0) {
            SW(0x240) = 0;
            base = 0xE00;
            SW(0x250) = 0x100;
            if (*(s32 *)(gGfx + 0x234) & 1) base = 0;
        } else {
            SW(0x240) = 0x100;
            base = 0xE80;
            SW(0x250) = 0x200;
            if (*(s32 *)(gGfx + 0x234) & 1) base = H;
        }
    } else {
        SW(0x230) = 0x200;
        base = 0xE00;
        H = 0x100;
        SW(0x240) = 0;
        SW(0x250) = 0x200;
        if (*(s32 *)(gGfx + 0x234) & 1) base = 0;
    }
    W_ = SW(0x230);
    X0 = SW(0x240);
    W2 = SW(0x250);

    {
        s32 e = SW(0x254) + SW(0x210);
        u8 *ee = tbl + e * 16;
        if (ee[0x28] != 0) {
            func_003126C8(sp, ee);
        } else {
            if ((*(u64 *)(D_003876A0 + 0x4D8) & 3) != 0) {
                sceVu0CopyMatrix(sp + 0x10, gBtlCam + (e << 8));
            } else {
                sceVu0CopyMatrix(sp + 0x10, gBtlCamView);
            }
            func_003126C8(sp + 0x40, D_002C3630);
            sceVu0ApplyMatrix(sp, sp + 0x10, D_00387B04 + (SW(0x254) + SW(0x210)) * 16);
        }
    }

    p = Dma_BeginDirect();
    Q(0x1000000000000008ULL, 0xE);
    Q(0x30000, 0x47);
    Q(0, 0x4A);
    Q(0x60, 0x14);
    Q((u64)(base | 0x24020000) | 0x240000000ULL, 6);
    SW(0x260) = H - 1;
    Q(0x40150, 0x4C);
    Q(0x1310000E0ULL, 0x4E);
    Q(((u64)(H - 1) << 16) | 0xDF000000000000ULL, 0x40);
    Q(((u64)(W_ - 1) << 14) | 0x6FC00000000ULL | 0xA, 8);
    Q(0x1000000000000003ULL, 0xE);
    Q(0x44, 0x42);
    Q(0x116, 0);
    Q(0x3F80000080808080ULL, 1);
    a2 = W_ >> 5;
    Q((u64)(a2 | 0x8000) | 0x4400000000000000ULL, 0x5353);
    if (a2 != 0) {
        lo = H / a2;
        if (a2 != 0) {
            s32 t0 = 0x7000, t1 = 0x200, a1 = lo * 16 + 0x7000;
            a3 = lo << 4;
            for (i = 0; i < a2; i++) {
                W(i << 9);
                W(t0 | 0x72000000);
                t0 += a3;
                W(t1 | 0x1C000000);
                W(a1 | 0x80000000ULL);
                t1 += 0x200;
                a1 += a3;
            }
        }
    }

    SW(0x270) = 1;
    SW(0x278) = H;
    SW(0x274) = (SW(0x254) + SW(0x210)) << 4;
    for (k = 0; k < 3; k++) {
        u8 *e3;
        if ((k & 1) == 0) {
            Q(0x1000000000000002ULL, 0xE);
            Q(0x220012A00ULL, 6);
            Q(0x4016C, 0x4C);
            SW(0x220) = 0x2D80;
        } else {
            Q(0x1000000000000002ULL, 0xE);
            Q(0x220012D80ULL, 6);
            Q(0x40150, 0x4C);
            SW(0x220) = 0x2A00;
        }
        e3 = D_00387B04 + SW(0x274);
        f3 = (f32)SW(0x270);
        f2 = SF(0);
        f4 = 16.0f;
        f0 = *(f32 *)(e3 + 0x14);
        f1 = *(f32 *)(e3 + 0x10);
        f0 = f3 * f0;
        f1 = f3 * f1;
        f0 = f0 * f2;
        f1 = f1 * f4;
        f0 = f0 * f4;
        s0 = (s32)f1;
        t6 = (s32)f0;
        s3 = 0;
        if (t6 < 0) {
            s3 = -t6;
            t6 = 0;
        }
        f0 = *(f32 *)(e3 + 0x18);
        f1 = SF(4);
        f0 = f3 * f0;
        f0 = f0 * f1;
        f0 = f0 * f4;
        t7 = (s32)f0;
        s6 = 0;
        if (t7 < 0) {
            s6 = -t7;
            t7 = 0;
        }
        a2 = H >> 5;
        Q(0x1000000000000002ULL, 0xE);
        Q(0x156, 0);
        Q(0x3F80000080808080ULL, 1);
        Q((u64)(a2 | 0x8000) | 0x4400000000000000ULL, 0x5353);
        lo = H / a2;
        if (a2 > 0) {
            s32 t0 = 8, t1 = 0x7000, t2 = 0x208, a1 = lo * 16 + 0x7000;
            a3 = lo << 4;
            for (i = 0; i < a2; i++) {
                W(t0 | 0x80000);
                t0 += 0x200;
                W(t1 | 0x72000000);
                t1 += a3;
                W(t2 | 0xE080000);
                t2 += 0x200;
                W(a1 | 0x80000000ULL);
                a1 += a3;
            }
        }
        a2 = SW(0x278) >> 5;
        {
            s32 sum = s0 + s3 + (t6 + s0);
            f1 = (f32)sum;
            f0 = (f32)a2;
        }
        Q(0x1000000000000002ULL, 0xE);
        Q(0x156, 0);
        Q(0x3F80000040808080ULL, 1);
        Q((u64)(a2 | 0x8000) | 0x4400000000000000ULL, 0x5353);
        lo = H / a2;
        f2 = f1 / f0;
        if (a2 > 0) {
            s32 a0 = -s0;
            s32 v1 = s0 + s6;
            s32 v0 = a0 - t7;
            s32 t1 = a0 - t6;
            s32 t3 = 0x7000, t4 = 0x208, t2 = 8, t5 = 0;
            s32 a1 = lo << 4;
            u64 sh0, sh7;
            s32 aa;
            a3 = a1 + 0x7000;
            v1 = 0x8000 + v1;
            v0 = v0 + 0x7200;
            sh0 = (u64)((s64)(s32)v0 << 16);
            sh7 = (u64)((s64)(s32)v1 << 16);
            for (; t5 < a2;) {
                s32 x0, x1;
                f32 g0 = (f32)t5;
                f32 g1 = (f32)(t5 + 1);
                t5 = t5 + 1;
                W(t2 | 0x80000);
                t2 += 0x200;
                g0 = f2 * g0;
                g1 = f2 * g1;
                aa = t4 | 0xE080000;
                t4 += 0x200;
                x0 = t1 + (s32)g0;
                x0 = t3 + x0;
                t3 += a1;
                x1 = t1 + (s32)g1;
                x1 = a3 + x1;
                a3 += a1;
                W(S64(x0) | sh0);
                W(aa);
                W(S64(x1) | sh7);
            }
        }
        SW(0x270) = SW(0x270) << 1;
    }

    Q(0x1000000000000006ULL, 0xE);
    Q((*(s32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070, 0x4C);
    Q(((u64)(W2 - 1) << 16) | (u64)X0 | 0x1BF000000000000ULL, 0x40);
    Q((u64)(0x20010000 | SW(0x220)) | 0x200000000ULL, 6);
    Q(((u64)SW(0x260) << 14) | 0x37C00000000ULL | 0xA, 8);
    Q(0x60, 0x14);
    Q(0x44, 0x42);

    {
        f32 g5, g4;
        s32 s4, t3, t4, t5, s2, t0, s1, a0, a1, a3_, v0, v1, tt;
        s32 s0_, t6_, a2_, t7_;
        g5 = (f32)SW(0x230);
        f1 = SF(0);
        g4 = (f32)D_00387B08;
        f0 = SF(4);
        f1 = f1 * 0.5f;
        f0 = f0 * 0.5f;
        f1 = f1 + 0.5f;
        f0 = f0 + 0.5f;
        f1 = f1 * 16.0f;
        f0 = f0 * 16.0f;
        f1 = f1 * g5;
        f0 = f0 * g4;
        s4 = (s32)f1;
        t3 = (s32)f0;
        {
            u32 u4 = (u32)s4 >> 31;
            u32 u3 = (u32)t3 >> 31;
            s32 t7x, a2x;
            s32 e2 = s4 >> 4, e6 = t3 >> 4;
            t7x = s4 + (s32)u4;
            t4 = e2 + (s32)u4;
            a2x = t3 + (s32)u3;
            t5 = e6 + (s32)u3;
            s0_ = t7x >> 5;
            s1 = a2x >> 5;
            v0 = W_ - e2;
            v1 = 0x1C0 - e6;
            a0 = H - s0_;
            a1 = 0xE0 - s1;
            v1 = v1 + (s32)((u32)v1 >> 31);
            a0 = a0 + (s32)((u32)a0 >> 31);
            v0 = v0 + (s32)((u32)v0 >> 31);
            a3_ = s0_ + (s32)((u32)t7x >> 31);
            t0 = s1 + (s32)((u32)a2x >> 31);
            a1 = a1 + (s32)((u32)a1 >> 31);
            s2 = e2 + (v0 >> 1);
            t6_ = e6 + (v1 >> 1);
            t4 = t4 >> 1;
            t5 = t5 >> 1;
            t0 = t0 >> 1;
            a3_ = a3_ >> 1;
            s0_ = s0_ + (a0 >> 1);
            s1 = s1 + (a1 >> 1);
            t7_ = t7x >> 1;
            a2_ = a2x >> 1;
        }
        SW(0x58) = s2;
        SW(0x5C) = t4;
        SW(0x64) = t5;
        SW(0x6C) = t6_;
        SW(0x84) = t0;
        SW(0x78) = s0_;
        SW(0x50) = t4;
        SW(0x54) = s2;
        SW(0x7C) = a3_;
        SW(0x60) = t5;
        SW(0x68) = t6_;
        SW(0x70) = a3_;
        SW(0x80) = t0;
        SW(0x74) = s0_;
        SW(0x8C) = s1;
        SW(0x88) = s1;
        tt = t3 + 0x7200;
        {
            u64 s3x = (u64)(s32)(((SW(0x240) + 0x700) << 4) + s4) | (u64)((s64)(s32)tt << 16);
            u64 a2o = (u64)t7_ | (u64)((s64)a2_ << 16);
            s32 e5 = (SW(0x254) + SW(0x210)) << 4;
            u8 *e4;
            SW(0x27C) = e5;
            Q(0x1000000000000001ULL, 0xE);
            Q(0x15D, 0);
            Q(0x3400000000008006ULL, 0x531);
            e4 = D_00387B04 + e5;
            Q((u64)*(u32 *)(e4 + 0x1C) | 0x3F80000000000000ULL, a2o);
            W(s3x);
        }
        {
            s32 t9 = 0;
            (void)t9;
            for (k = 0; k < 5; k++) {
                s32 off = (k % 4) * 4;
                s32 va, vb;
                W((u64)*(u32 *)(D_00387B04 + SW(0x27C) + 0x20) | 0x3F80000000000000ULL);
                va = SW(0x80 + off);
                vb = SW(0x70 + off);
                W(S64(vb << 4) | ((u64)(s64)(s32)(va << 4) << 16));
                va = SW(0x60 + off);
                vb = SW(0x50 + off);
                W((u64)(s64)(s32)(((SW(0x240) + vb) << 4) + 0x7000) | ((u64)(s64)(s32)((va << 4) + 0x7200) << 16));
            }
        }
    }

    /* build the two index tables on the stack */
    SW(0x120) = SW(0x54); SW(0x124) = SW(0x64); SW(0x128) = SW(0x50); SW(0x12C) = SW(0x60);
    SW(0x118) = SW(0x230); SW(0x140) = SW(0x58); SW(0x144) = SW(0x68); SW(0x148) = SW(0x54);
    SW(0x160) = SW(0x5C); SW(0x14C) = SW(0x64);
    SW(0x110) = 0; SW(0x114) = 0; SW(0x11C) = 0;
    SW(0x130) = SW(0x230); SW(0x134) = 0; SW(0x138) = SW(0x230); SW(0x13C) = 0x1C0;
    SW(0x150) = SW(0x230); SW(0x154) = 0x1C0; SW(0x158) = 0; SW(0x15C) = 0x1C0;
    SW(0x164) = SW(0x6C); SW(0x168) = SW(0x58); SW(0x16C) = SW(0x68);
    SW(0x174) = 0x1C0; SW(0x180) = SW(0x50); SW(0x184) = SW(0x60); SW(0x188) = SW(0x5C); SW(0x18C) = SW(0x6C);
    SW(0x170) = 0; SW(0x178) = 0; SW(0x17C) = 0;
    __builtin_memcpy(sp + 0x90, sp + 0x110, 0x80);

    SW(0x1A8) = SW(0x70); SW(0x1AC) = SW(0x80); SW(0x1C4) = SW(0x88);
    SW(0x1A4) = SW(0x84); SW(0x1A0) = SW(0x74); SW(0x1C0) = SW(0x78);
    SW(0x1C8) = SW(0x74); SW(0x1E0) = SW(0x7C); SW(0x1CC) = SW(0x84); SW(0x1E4) = SW(0x8C);
    SW(0x190) = 0; SW(0x194) = 0; SW(0x198) = H; SW(0x19C) = 0;
    SW(0x1B0) = H; SW(0x1B4) = 0; SW(0x1B8) = H; SW(0x1BC) = 0xE0;
    SW(0x1D0) = H; SW(0x1D4) = 0xE0; SW(0x1D8) = 0; SW(0x1DC) = 0xE0;
    SW(0x1E8) = SW(0x78); SW(0x1EC) = SW(0x88);
    SW(0x1F4) = 0xE0; SW(0x200) = SW(0x70); SW(0x204) = SW(0x80); SW(0x208) = SW(0x7C); SW(0x20C) = SW(0x8C);
    SW(0x1F0) = 0; SW(0x1F8) = 0; SW(0x1FC) = 0;
    {
        /* second copy: 0x190..0x20F -> 0x110..0x18F (idx at 0x210 is left alone) */
        s32 *src = (s32 *)(sp + 0x190);
        s32 *dst = (s32 *)(sp + 0x110);
        for (i = 0; i < 32; i++) dst[i] = src[i];
    }
    {
        u8 *e6p = D_00387B04 + ((SW(0x254) + SW(0x210)) << 4);
        s32 t8, t3 = 0;
        u8 *t5p = sp + 0x90, *t6p = sp + 0x110, *t7p = sp + 0x190;
        SW(0x1D0) = *(s32 *)(e6p + 0x24);
        SW(0x1D4) = *(s32 *)(e6p + 0x24);
        SW(0x1D8) = *(s32 *)(e6p + 0x20);
        SW(0x1DC) = *(s32 *)(e6p + 0x20);
        SW(0x1E0) = *(s32 *)(e6p + 0x24);
        SW(0x1E4) = *(s32 *)(e6p + 0x24);
        SW(0x1E8) = *(s32 *)(e6p + 0x20);
        SW(0x1EC) = *(s32 *)(e6p + 0x20);
        SW(0x1F0) = *(s32 *)(e6p + 0x24);
        SW(0x1F4) = *(s32 *)(e6p + 0x24);
        SW(0x1F8) = *(s32 *)(e6p + 0x20);
        SW(0x1FC) = *(s32 *)(e6p + 0x20);
        SW(0x200) = *(s32 *)(e6p + 0x24);
        SW(0x204) = *(s32 *)(e6p + 0x24);
        SW(0x208) = *(s32 *)(e6p + 0x20);
        SW(0x20C) = *(s32 *)(e6p + 0x20);
        __builtin_memcpy(sp + 0x190, sp + 0x1D0, 0x40);
        for (t8 = 0; t8 < 4; t8++, t3 += 4) {
            u8 *t0p = t6p + t3 * 8;
            u8 *t1p = t7p + t3 * 4;
            u8 *a3p = t5p + t3 * 8;
            s32 r;
            Q(0x1000000000000001ULL, 0xE);
            Q(0x15D, 0);
            Q(0x3400000000008004ULL, 0x531);
            for (r = 0; r < 4; r++) {
                s32 va, vb;
                W((u64)*(u32 *)t1p | 0x3F80000000000000ULL);
                va = *(s32 *)(t0p + 0);
                vb = *(s32 *)(t0p + 4);
                W(S64(va << 4) | ((u64)(s64)(s32)(vb << 4) << 16));
                va = *(s32 *)(a3p + 0);
                vb = *(s32 *)(a3p + 4);
                W((u64)(s64)(s32)(((SW(0x240) + va) << 4) + 0x7000) | ((u64)(s64)(s32)((vb << 4) + 0x7200) << 16));
                t0p += 8;
                a3p += 8;
                t1p += 4;
            }
        }
    }
    Q(0x1000000000008002ULL, 0xE);
    Q(0x310000E0ULL, 0x4E);
    Q(0x1BF000001FF0000ULL, 0x40);
    Dma_EndDirect(p);
}
