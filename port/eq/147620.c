#include "common.h"

extern u8 *gBtlCamView;
extern u8 *D_00387758;
extern u64 D_0036DE00[4];
extern u64 D_0036DE20[2];
extern u64 D_0036DE30[2];

extern s32 sceVu0InversMatrix(u8 *dst, u8 *src);
extern s32 sceVu0ApplyMatrix(u8 *dst, u8 *m, u8 *v);
extern f32 sceVu0InnerProduct(u8 *a, u8 *b);
extern u64 *Dma_BeginDirect(void);
extern void Dma_EndDirect();
extern void func_00147508(u8 *entry, u8 *vec);
extern void func_00312650(u8 *dst, u8 *a, u8 *b);
extern void func_00312638(u8 *dst, u8 *a, u8 *b);
extern void func_00135EA0(s32 *dst, u8 *src);
extern void func_00312680(u8 *dst, u8 *src, f32 s);
extern f32 sqrtf(f32 x);

/* Draws the 512 + 2304 line-segment sprites (64-byte records at D_00387758 and D_00387758 + 0x8000) as GIF
   packets: each segment is projected from its start (312650) and end (312638); it is drawn when either end is
   inside the screen window (x 0x6C01..0x93FF, y 0x6E81..0x917F, z > 0). */
void func_00147620(void) {
    u8 sp[0xC0];
    u8 *rec;
    u8 *vA = sp + 0x00;      /* uv pair 0 (0,0) and 1 (1,1,..) at +0x10 */
    u8 *vB = sp + 0x20;      /* (0,0,500,1) transformed */
    u8 *vC = sp + 0x30;      /* (3,3,0,0) transformed */
    s32 *e0 = (s32 *)(sp + 0xA0);
    s32 *e1 = (s32 *)(sp + 0xB0);
    u64 *p;
    s32 i;
    s32 ok0;
    s32 ok1;
    f32 d;
    f32 f;

    ((u64 *)sp)[0] = D_0036DE00[0];
    ((u64 *)sp)[1] = D_0036DE00[1];
    ((u64 *)sp)[2] = D_0036DE00[2];
    ((u64 *)sp)[3] = D_0036DE00[3];
    ((u64 *)sp)[4] = D_0036DE20[0];
    ((u64 *)sp)[5] = D_0036DE20[1];
    ((u64 *)sp)[6] = D_0036DE30[0];
    ((u64 *)sp)[7] = D_0036DE30[1];
    sceVu0InversMatrix(sp + 0x60, gBtlCamView);
    sceVu0ApplyMatrix(vB, sp + 0x60, vB);
    sceVu0ApplyMatrix(vC, sp + 0x60, vC);

    p = Dma_BeginDirect();
    p[0] = 0x1000000000008004ULL;
    p[1] = 0xE;
    p[2] = 0x1310000E0ULL;
    p[3] = 0x4E;
    p[4] = 0x48;
    p[5] = 0x42;
    p[6] = *(u64 *)(D_00387758 + 0x2C000);
    p[7] = 6;
    p[8] = 0x73003;
    p[9] = 0x47;
    Dma_EndDirect(p + 10);

    rec = D_00387758;
    for (i = 0x1FF; i >= 0; i--, rec += 0x40) {
        u8 *box;
        s32 inside;

        func_00147508(rec, vB);
        box = *(u8 **)(*(u8 **)(D_00387758 + 0x2C210) + 0x14);
        inside = 0;
        if (*(f32 *)(box + 0x00) < *(f32 *)(rec + 0x00) && *(f32 *)(rec + 0x00) < *(f32 *)(box + 0x10)
            && *(f32 *)(box + 0x08) < *(f32 *)(rec + 0x08) && *(f32 *)(rec + 0x08) < *(f32 *)(box + 0x18)) {
            inside = 1;
        }
        if (!inside) {
            continue;
        }
        func_00312650(sp + 0x40, rec, vC);
        func_00135EA0(e0, sp + 0x40);
        func_00312638(sp + 0x40, rec, vC);
        func_00135EA0(e1, sp + 0x40);
        ok0 = 0;
        if (e0[2] > 0 && e0[0] <= 0x93FF && e0[0] >= 0x6C01 && e0[1] <= 0x917F) {
            ok0 = e0[1] >= 0x6E81;
        }
        if (!ok0) {
            ok1 = 0;
            if (e1[2] > 0 && e1[0] <= 0x93FF && e1[0] >= 0x6C01 && e1[1] <= 0x917F) {
                ok1 = e1[1] >= 0x6E81;
            }
            if (!ok1) {
                continue;
            }
        }
        p = Dma_BeginDirect();
        p[0] = 0x6400000000000001ULL;
        p[1] = 0x525210;
        p[2] = 0x56;
        p[3] = 0x3F80000040808080ULL;
        p[4] = (u64)*(u32 *)(sp + 0x00) | ((u64)*(u32 *)(sp + 0x04) << 32);
        p[5] = (u64)(s64)e0[0] | ((u64)(s64)e0[1] << 16) | ((u64)(s64)e0[2] << 32);
        p[6] = (u64)*(u32 *)(sp + 0x10) | ((u64)*(u32 *)(sp + 0x14) << 32);
        p[7] = (u64)(s64)e1[0] | ((u64)(s64)e1[1] << 16) | ((u64)(s64)e1[2] << 32);
        Dma_EndDirect(p + 8);
    }

    p = Dma_BeginDirect();
    p[0] = 0x1000000000008004ULL;
    p[1] = 0xE;
    p[2] = 0x1310000E0ULL;
    p[3] = 0x4E;
    p[4] = 0x44;
    p[5] = 0x42;
    p[6] = *(u64 *)(D_00387758 + 0x2C010);
    p[7] = 6;
    p[8] = 0x73003;
    p[9] = 0x47;
    Dma_EndDirect(p + 10);
    func_00312680(vC, vC, 8.0f);

    rec = D_00387758 + 0x8000;
    for (i = 0x8FF; i >= 0; i--, rec += 0x40) {
        if (*(s32 *)(rec + 0x28) < 0) {
            continue;
        }
        func_00312650(sp + 0x50, rec, sp + 0x90);
        *(f32 *)(sp + 0x5C) = 1.0f;
        *(f32 *)(sp + 0x54) = 1.0f;
        d = __builtin_sqrtf(sceVu0InnerProduct(sp + 0x50, sp + 0x50));
        f = 1.0f - d / 800.0f;
        if (!(0.0f < f)) {
            continue;
        }
        if (!(f < 1.0f)) {
            continue;
        }
        d = *(f32 *)(rec + 0x34);
        if (!(0.0f < d)) {
            continue;
        }
        *(u64 *)(rec + 0x20) = ((u64)(s64)(s32)((f * 64.0f) * d) << 24) | 0x3F80000000808080ULL;
        func_00312650(sp + 0x40, rec, vC);
        func_00135EA0(e0, sp + 0x40);
        func_00312638(sp + 0x40, rec, vC);
        func_00135EA0(e1, sp + 0x40);
        ok0 = 0;
        if (e0[2] > 0 && e0[0] <= 0x93FF && e0[0] >= 0x6C01 && e0[1] <= 0x917F) {
            ok0 = e0[1] >= 0x6E81;
        }
        if (!ok0) {
            ok1 = 0;
            if (e1[2] > 0 && e1[0] <= 0x93FF && e1[0] >= 0x6C01 && e1[1] <= 0x917F) {
                ok1 = e1[1] >= 0x6E81;
            }
            if (!ok1) {
                continue;
            }
        }
        p = Dma_BeginDirect();
        p[0] = 0x6400000000000001ULL;
        p[1] = 0x525210;
        p[2] = 0x56;
        p[3] = *(u64 *)(rec + 0x20);
        p[4] = (u64)*(u32 *)(sp + 0x00) | ((u64)*(u32 *)(sp + 0x04) << 32);
        p[5] = (u64)(s64)e0[0] | ((u64)(s64)e0[1] << 16) | ((u64)(s64)e0[2] << 32);
        p[6] = (u64)*(u32 *)(sp + 0x10) | ((u64)*(u32 *)(sp + 0x14) << 32);
        p[7] = (u64)(s64)e1[0] | ((u64)(s64)e1[1] << 16) | ((u64)(s64)e1[2] << 32);
        Dma_EndDirect(p + 8);
    }
}
