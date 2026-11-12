#include "common.h"

extern u8 D_002C3630[];
extern u8 *D_003876A0;
extern u8 *D_00387F2C;

extern s32 Res_RelocateOffsets();
extern s32 func_00269F00();
extern s32 func_0025CD10();
extern s32 func_0025CE28();
extern s32 func_0025CCC8();
extern s32 func_0025CDA0();
extern s32 func_0025D100();
extern s32 func_0026A378();
extern s32 func_0025DEC0();
extern s32 func_003126C8();
extern s32 sceVu0UnitMatrix();
extern s32 func_002604A8();
extern s32 func_002673C0();

/* if ([g+o+4] != [g+o]) *dst = g + ([g+o] & ~3) */
static void setIf(u8 *dst, u8 *g, s32 o)
{
    u32 a = *(u32 *)(g + o);
    u32 b = *(u32 *)(g + o + 4);
    if (b != a) *(u8 **)dst = g + (a & ~3u);
}

/* same but stores 0 when equal */
static void setOr0(u8 *dst, u8 *g, s32 o)
{
    u32 a = *(u32 *)(g + o);
    u32 b = *(u32 *)(g + o + 4);
    if (b == a) *(u8 **)dst = 0;
    else *(u8 **)dst = g + (a & ~3u);
}

s32 func_0025D190(u8 *a0)
{
    u8 *s3, *g, *r, *w, *p;
    s32 i, v, n, base;
    u32 flags;
    u8 *s4 = a0 + 0xAF0;

    *(s32 *)(a0 + 0xC) = 1;
    *(s32 *)(a0 + 0x14) = 0;
    s3 = *(u8 **)(a0 + 0x18);
    g = *(u8 **)(s3 + 0x24);
    *(u8 **)(a0 + 0x1C) = g + (*(u32 *)(g + 0xC) & ~3u);
    *(u8 **)(a0 + 0x20) = g + (*(u32 *)(g + 0x10) & ~3u);
    g = *(u8 **)(s3 + 0x24);
    setIf(a0 + 0x958, g, 0x48);
    setIf(a0 + 0x95C, g, 0x5C);
    setIf(a0 + 0x978, g, 0x50);
    setIf(a0 + 0x980, g, 0x60);
    setIf(a0 + 0x984, g, 0x64);
    setIf(a0 + 0x974, g, 0x4C);
    setIf(a0 + 0x98C, g, 0x54);
    if (*(u32 *)(g + 8) == *(u32 *)(g + 4)) {
        *(s32 *)(a0 + 0x988) = 0;
        *(s32 *)(a0 + 0x990) = 0;
    } else {
        setIf(a0 + 0x988, g, 0x3E8);
        setIf(a0 + 0x990, g, 0x3E4);
    }
    setOr0(a0 + 0x744, g, 8);
    r = *(u8 **)(s3 + 0x28);
    flags = 0;
    if (r) {
        flags = (u32)*(u64 *)(D_003876A0 + 0x4D8) & 3;
        n = flags ? 0x1B1 : 0x32;
        for (i = 0; i < n; i++) {
            r = *(u8 **)(s3 + 0x28);
            setIf(a0 + 0x60 + i * 4, r, 4 + i * 4);
        }
    }
    g = *(u8 **)(s3 + 0x24);
    for (i = 0; i < 8; i++) {
        g = *(u8 **)(s3 + 0x24);
        setIf(a0 + 0x724 + i * 4, g, 0x68 + i * 4);
    }
    r = *(u8 **)(s3 + 0x2C);
    if (r) {
        for (i = 0; i < 6; i++) {
            u8 *a3 = a0 + 0x940 + i * 4;
            s32 t0;
            if (i == 5) {
                *(s32 *)(a0 + 0x954) = 0;
                t0 = i * 4;
            } else {
                r = *(u8 **)(s3 + 0x2C);
                t0 = i * 4;
                setIf(a3, r, 4 + i * 4);
            }
            p = *(u8 **)a3;
            if (p) {
                setIf(a0 + 0x960 + t0, p, 4);
            }
        }
    }
    g = *(u8 **)(s3 + 0x24);
    setOr0(a0 + 0x748, g, 0x98);
    setOr0(a0 + 0x74C, g, 0x9C);
    setOr0(a0 + 0x750, g, 0xA0);
    for (i = 0; i < 8; i++) {
        g = *(u8 **)(s3 + 0x24);
        setOr0(a0 + 0x910 + i * 4, g, 0x68 + i * 4);
    }
    for (i = 0; i < 4; i++) {
        g = *(u8 **)(s3 + 0x24);
        setOr0(a0 + 0x930 + i * 4, g, 0x88 + i * 4);
    }
    g = *(u8 **)(s3 + 0x24);
    setOr0(a0 + 0x97C, g, 0x58);
    base = (*(u32 *)(D_00387F2C + 0x1008) & 1) ? 100 : 0;
    g = *(u8 **)(s3 + 0x24);
    n = (*(u32 *)(g + 8) == *(u32 *)(g + 4)) ? 0x46 : 0x64;
    for (i = 0; i < n; i++) {
        g = *(u8 **)(s3 + 0x24);
        setOr0(a0 + 0x780 + i * 4, g, 0xC4 + (base + i) * 4);
    }
    for (i = 0; i < 11; i++) {
        g = *(u8 **)(s3 + 0x24);
        setOr0(a0 + 0x754 + i * 4, g, 0x1C + i * 4);
    }
    g = *(u8 **)(s3 + 0x24);
    setOr0(a0 + 0x5C, g, 0xC0);

    w = *(u8 **)(a0 + 0x1C);
    *(u8 **)(a0 + 0x44) = w;
    *(u8 **)(a0 + 0x48) = w + *(s32 *)(w + 4);
    v = *(s32 *)a0;
    v = v - (((v + ((u32)v >> 31)) >> 1) << 1);
    if (v == 0) {
        *(s32 *)(s4 + 0xBC) = 0x3480;
        *(s32 *)(s4 + 0xC0) = 0x3C00;
        *(s32 *)(s4 + 0xCC) = 0x3D00;
        *(s32 *)(s4 + 0xC4) = 0x3D40;
        *(s32 *)(s4 + 0xC8) = 0x3E40;
    } else if (v == 1) {
        *(s32 *)(s4 + 0xBC) = 0x30C0;
        *(s32 *)(s4 + 0xC0) = 0x3AC0;
        *(s32 *)(s4 + 0xCC) = 0x3BC0;
        *(s32 *)(s4 + 0xC4) = 0x3DC0;
        *(s32 *)(s4 + 0xC8) = 0x3E44;
    }
    w = *(u8 **)(a0 + 0x44);
    *(f32 *)(s4 + 0xAC) = (*(f32 *)(w + 0x30) == 0.0f) ? 18.0f : *(f32 *)(w + 0x30);
    w = *(u8 **)(a0 + 0x44);
    *(f32 *)(s4 + 0xB0) = (*(f32 *)(w + 0x34) == 0.0f) ? 120.0f : *(f32 *)(w + 0x34);
    w = *(u8 **)(a0 + 0x44);
    *(f32 *)(s4 + 0xB4) = (*(f32 *)(w + 0x38) == 0.0f) ? 40.0f : *(f32 *)(w + 0x38);
    w = *(u8 **)(a0 + 0x44);
    *(f32 *)(s4 + 0xB8) = (*(f32 *)(w + 0x3C) == 0.0f) ? 120.0f : *(f32 *)(w + 0x3C);

    Res_RelocateOffsets(a0 + 0x4C, *(s32 *)(a0 + 0x20), *(s32 *)(a0 + 0x20));
    g = *(u8 **)(s3 + 0x24);
    if (*(u32 *)(g + 0x18) == *(u32 *)(g + 0x14)) {
        *(s32 *)(a0 + 0x50) = 0;
    } else {
        p = g + (*(u32 *)(g + 0x14) & ~3u);
        *(u8 **)(a0 + 0x50) = p;
        Res_RelocateOffsets(a0 + 0x50, p, p);
    }
    g = *(u8 **)(s3 + 0x24);
    if (*(u32 *)(g + 0x1C) == *(u32 *)(g + 0x18)) {
        *(s32 *)(a0 + 0x54) = 0;
    } else {
        p = g + (*(u32 *)(g + 0x18) & ~3u);
        *(u8 **)(a0 + 0x54) = p;
        Res_RelocateOffsets(a0 + 0x54, p, p);
    }
    g = *(u8 **)(s3 + 0x24);
    if (*(u32 *)(g + 8) == *(u32 *)(g + 4)) {
        *(s32 *)(a0 + 0x58) = 0;
    } else {
        p = g + (*(u32 *)(g + 4) & ~3u);
        *(u8 **)(a0 + 0x58) = p;
        Res_RelocateOffsets(a0 + 0x58, p, p);
    }
    w = *(u8 **)(a0 + 0x44);
    if (*(s32 *)w < 0) {
        *(s32 *)(s4 + 0xBC) = *(u16 *)(w + 0x40);
        w = *(u8 **)(a0 + 0x44);
        *(s32 *)(s4 + 0xC0) = *(u16 *)(w + 0x42);
        w = *(u8 **)(a0 + 0x44);
        *(s32 *)(s4 + 0xCC) = *(u16 *)(w + 0x44);
        w = *(u8 **)(a0 + 0x44);
        *(s32 *)(s4 + 0xC4) = *(u16 *)(w + 0x46);
        w = *(u8 **)(a0 + 0x44);
        *(s32 *)(s4 + 0xC8) = *(u16 *)(w + 0x48);
        w = *(u8 **)(a0 + 0x44);
        v = *(u16 *)(w + 0x4A);
        *(s32 *)(s4 + 4) = v;
        func_0025CCC8(v);
    } else {
        u8 *s1 = a0 + 0x754;
        func_00269F00(0, *(s32 *)(a0 + 0x48), *(s32 *)(s4 + 0xBC), *(s32 *)(s4 + 0xC0), 0x3D40,
                      *(s32 *)(s4 + 0xCC), 0x7FFFFFFF, 0x7FFFFFFF);
        for (i = 10; i >= 0; i--) {
            u8 *e = *(u8 **)s1;
            s1 += 4;
            if (e) {
                func_00269F00(1, e, *(s32 *)(s4 + 0xBC), *(s32 *)(s4 + 0xC0), 0x3D40,
                              *(s32 *)(s4 + 0xCC), 0, 0);
            }
        }
        v = func_0025CD10(a0);
        *(s32 *)(s4 + 4) = v;
        func_0025CE28(a0, v);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x40) = *(u16 *)(s4 + 0xBC);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x42) = *(u16 *)(s4 + 0xC0);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x44) = *(u16 *)(s4 + 0xCC);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x46) = *(u16 *)(s4 + 0xC4);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x48) = *(u16 *)(s4 + 0xC8);
        w = *(u8 **)(a0 + 0x44);
        *(u16 *)(w + 0x4A) = *(u16 *)(s4 + 4);
        w = *(u8 **)(a0 + 0x44);
        *(u32 *)w |= 0x80000000u;
    }
    func_0025CDA0(a0, *(s32 *)(s4 + 4));
    func_0025D100(a0);
    g = *(u8 **)(s3 + 0x24);
    if (*(u32 *)(g + 0x60) != *(u32 *)(g + 0x5C)) {
        func_0026A378(a0);
    }
    func_0025DEC0(a0, 0);
    func_003126C8(a0 + 0x9A0, D_002C3630);
    func_003126C8(a0 + 0x9C0, D_002C3630);
    func_003126C8(a0 + 0x9B0, D_002C3630);
    sceVu0UnitMatrix(a0 + 0xA00);
    func_003126C8(a0 + 0xD20, D_002C3630);
    func_003126C8(a0 + 0xD30, D_002C3630);
    func_003126C8(a0 + 0xD40, D_002C3630);
    *(f32 *)(a0 + 0x9F4) = 1.0f;
    *(f32 *)(a0 + 0xD84) = 1.0f;
    *(f32 *)(a0 + 0xBE8) = 2.0f;
    func_002604A8(a0);
    return func_002673C0(a0);
}
