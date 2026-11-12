#include "common.h"
#include "vu0_state.h"

#define SI(o) (*(s32 *)(sp + (o)))
#define SU(o) (*(u32 *)(sp + (o)))
#define SF(o) (*(f32 *)(sp + (o)))

extern u8 *D_00388714 __attribute__((section(".data")));
extern u8 *gEftBurst;
extern f32 D_003842A0;
extern f32 D_003842A4;
extern u8 D_0036DC90[16];
extern u8 D_0036DCA0[16];

extern void EftBurst_SetTexture(u8 *tex, s32 a1, s32 a2);
extern void EftBurst_ClearAlphaPlane(void);
extern u64 *Dma_BeginDirect(void);
extern u64 *EftBurst_PutModelEnv(u64 *p);
extern u64 *EftBurst_PutModelEnvEnd(u64 *p);
extern void Dma_EndDirect(u64 *end);
extern void func_00312638(u8 *dst, u8 *a, u8 *b);   /* dst = a + b */
extern void func_00312650(u8 *dst, u8 *a, u8 *b);   /* dst = a - b */
extern void func_00312680(u8 *dst, u8 *src, f32 s); /* dst = src * s */
extern void func_003126C8(u8 *dst, u8 *src);        /* 16-byte copy */
extern void func_00312710(u8 *dst, u8 *src);        /* ftoi0 */
extern void func_00312730(u8 *dst, u8 *src);        /* itof0 */
extern f32 sceVu0InnerProduct(u8 *a, u8 *b);
extern void sceVu0ClampVector(u8 *dst, u8 *src, f32 min, f32 max);
extern f32 sqrtf(f32 x);

/* VU0 ftoi: truncates toward zero and saturates to the s32 range */
static s32 vu_ftoi(f32 x) {
    if (x >= 2147483648.0f) return 0x7FFFFFFF;
    if (x <= -2147483648.0f) return (s32)0x80000000;
    return (s32)x;
}

/* Draws the burst-effect triangle lists (gEftBurst): per entry, groups of 3 vertices are transformed with the
   VU0 matrix in gVu0.vf[24..27], vertex colours (and an optional lit second pass) are built, and GIF packets
   are emitted for the triangles that have a vertex on screen. */
void func_00134BA0(u8 *arg) {
    u8 sp[0x200] __attribute__((aligned(16)));
    u8 *list = *(u8 **)(arg + 8);
    u8 *texBase = *(u8 **)(arg + 0x10);
    u8 *texB = *(u8 **)(D_00388714 + 0x10) + 0x180;
    s32 count = *(s32 *)(arg + 4);
    f32 fadeScale, fadeDist;
    u64 *d;
    f32 f24 = 8.0f;

    __builtin_memset(sp, 0, 16);
    SF(8) = -50.0f;
    fadeScale = (f32)*(s32 *)(gEftBurst + 4) * D_003842A0;
    fadeDist = *(f32 *)(gEftBurst + 8);
    if (1.0f < fadeScale) fadeScale = 1.0f;

    EftBurst_SetTexture(NULL, 0, 0);
    EftBurst_ClearAlphaPlane();
    d = Dma_BeginDirect();
    d = EftBurst_PutModelEnv(d);
    Dma_EndDirect(d);

    if (count > 0) {
        s32 remaining = count;
        do {
            s32 flags = *(s32 *)list;
            u8 *tex = texBase + (*(s32 *)(list + 4) << 6);
            u8 *verts = *(u8 **)(list + 8);
            u8 *grp = *(u8 **)(list + 0xC);
            f32 scale = *(f32 *)(list + 0x10);
            s32 w, h, g;
            s32 lit = flags & 0x800;

            EftBurst_SetTexture(tex, 0x2D00, 0x2A00);
            w = *(s32 *)(tex + 0x10) + 0x2D00;
            h = *(s32 *)(tex + 0x14) + 0x2A00;
            *(s32 *)(tex + 0x20) = 0x2D00;
            *(s32 *)(tex + 0x24) = 0x2A00;
            EftBurst_SetTexture(texB, w, h);
            *(s32 *)(texB + 0x20) = w;
            *(s32 *)(texB + 0x24) = h;

            d = Dma_BeginDirect();
            d[0] = 0x1000000000008004ULL; d[1] = 0xE;
            d[2] = 0; d[3] = 8;
            d[4] = 0; d[5] = 9;
            d[6] = 0x42; d[7] = 0x44;
            d[8] = 0x44; d[9] = 0x43;
            d += 10;

            if (*(s16 *)(list + 0x14) > 0) {
                for (g = 0; g < *(s16 *)(list + 0x14); g++, grp += 0x1E) {
                    s32 onScreen = 0;
                    s32 i;
                    u64 *out = (u64 *)(sp + 0xD0);
                    for (i = 0; i < 3; i++) {
                        u8 *v = verts + *(s16 *)(grp + i * 2) * 6;
                        f32 P[4], R[4], q;
                        f32 *uv = (f32 *)(sp + 0x70 + i * 16);
                        s32 *scr = (s32 *)(sp + 0x40 + i * 16);
                        u8 *col = grp + 0x12 + i * 4;
                        s32 cr, cg, cb, ca;
                        s32 flag = 0;
                        s32 k;

                        P[0] = (f32)*(s16 *)(v + 0) / 4096.0f;
                        P[1] = (f32)*(s16 *)(v + 2) / 4096.0f;
                        P[2] = (f32)*(s16 *)(v + 4) / 4096.0f;
                        P[3] = 0.0f;
                        __builtin_memcpy(sp + 0x30, P, 16);
                        uv[0] = (f32)*(s16 *)(grp + 6 + i * 4) / 4096.0f;
                        uv[1] = (f32)*(s16 *)(grp + 8 + i * 4) / 4096.0f;
                        uv[2] = 0.0f;
                        uv[3] = 0.0f;
                        func_00312680(sp + 0x30, sp + 0x30, scale);
                        func_00312650(sp + 0x10, sp, sp + 0x30);
                        SF(0x3C) = 1.0f;
                        for (k = 0; k < 4; k++)
                            R[k] = gVu0.vf[24][k] * SF(0x30) + gVu0.vf[25][k] * SF(0x34) +
                                   gVu0.vf[26][k] * SF(0x38) + gVu0.vf[27][k] * SF(0x3C);
                        uv[2] = gVu0.vf[13][2];
                        q = R[3] != 0.0f ? 1.0f / R[3] : __builtin_copysignf(3.4028235e38f, R[3]); /* VU vdiv by 0: +-FLT_MAX */
                        gVu0.q = q;
                        R[0] *= q; R[1] *= q; R[2] *= q;
                        uv[0] *= q; uv[1] *= q; uv[2] *= q;
                        scr[0] = vu_ftoi(R[0] * 16.0f);
                        scr[1] = vu_ftoi(R[1] * 16.0f);
                        scr[2] = vu_ftoi(R[2]);
                        scr[3] = vu_ftoi(R[3]);

                        cr = col[0]; cg = col[1]; cb = col[2]; ca = col[3];
                        SI(0x100) = cr; SI(0x104) = cg; SI(0x108) = cb; SI(0x10C) = ca;
                        out[i * 2] = (u64)(s64)cr | ((u64)SU(0x78 + i * 16) << 32) | ((s64)cb << 16) |
                                     ((s64)cg << 8) | ((s64)ca << 24);
                        if (lit) {
                            func_003126C8(sp + 0xA0 + i * 16, sp + 0x70 + i * 16);
                            SF(0xA0 + i * 16) = SF(0xA0 + i * 16) * f24;
                            SF(0xA4 + i * 16) = SF(0xA4 + i * 16) * f24;
                            if (*(s32 *)(gEftBurst + 4) < 11) {
                                out[i * 2 + 1] = (u64)SU(0x78 + i * 16) << 32;
                            } else {
                                f32 dist, fade;
                                __builtin_memset(sp + 0x110, 0, 16);
                                SF(0x11C) = 1.0f;
                                __builtin_memcpy(sp + 0x120, D_0036DC90, 16);
                                __builtin_memcpy(sp + 0x130, D_0036DCA0, 16);
                                dist = __builtin_sqrtf(__builtin_fabsf(sceVu0InnerProduct(sp + 0x10, sp + 0x10))); /* sqrt.s uses |x| */
                                fade = 255.0f - (dist / fadeDist) * 255.0f;
                                if (255.0f < fade) fade = 255.0f;
                                func_00312730(sp + 0x140, sp + 0x100);
                                func_00312680(sp + 0x110, sp + 0x110, fadeScale * D_003842A4 * fade);
                                func_00312638(sp + 0x130, sp + 0x110, sp + 0x130);
                                sceVu0ClampVector(sp + 0x130, sp + 0x130, 0.0f, 255.0f);
                                func_00312710(sp + 0x100, sp + 0x130);
                                out[i * 2 + 1] = (u64)(s64)SI(0x100) | ((u64)SU(0x78 + i * 16) << 32) |
                                                 ((s64)SI(0x108) << 16) | ((s64)SI(0x104) << 8) |
                                                 ((s64)SI(0x10C) << 24);
                                if (dist < fadeDist) {
                                    func_00312680(sp + 0x120, sp + 0x120, fade);
                                    func_00312638(sp + 0x130, sp + 0x120, sp + 0x140);
                                    sceVu0ClampVector(sp + 0x130, sp + 0x130, 0.0f, 255.0f);
                                    func_00312710(sp + 0x100, sp + 0x130);
                                    out[i * 2] = (u64)(s64)SI(0x100) | ((u64)SU(0x78 + i * 16) << 32) |
                                                 ((s64)SI(0x108) << 16) | ((s64)SI(0x104) << 8) |
                                                 ((s64)SI(0x10C) << 24);
                                }
                            }
                        }
                        if (scr[2] > 0) {
                            if (scr[0] <= 0x97FF && scr[0] >= 0x6801 && scr[1] <= 0x94FF)
                                flag = scr[1] >= 0x6B01;
                        }
                        onScreen += flag;
                    }
                    if (onScreen != 0) {
                        d[0] = 0x1000000000008002ULL; d[1] = 0xE;
                        d[2] = *(u64 *)(tex + 0x30) | 0x54004ULL << 32 | 0x2D00; d[3] = 6;
                        d[4] = 0x5B; d[5] = 0;
                        d[6] = 0x3400000000008003ULL; d[7] = 0x521;
                        d[8] = *(u64 *)(sp + 0xD0);
                        d[9] = (u64)SU(0x70) | (u64)SU(0x74) << 32;
                        d[10] = (u64)(s64)SI(0x40) | (u64)((s64)SI(0x44) << 16) | (u64)((s64)SI(0x48) << 32);
                        d[11] = *(u64 *)(sp + 0xE0);
                        d[12] = (u64)SU(0x80) | (u64)SU(0x84) << 32;
                        d[13] = (u64)(s64)SI(0x50) | (u64)((s64)SI(0x54) << 16) | (u64)((s64)SI(0x58) << 32);
                        d[14] = *(u64 *)(sp + 0xF0);
                        d[15] = (u64)SU(0x90) | (u64)SU(0x94) << 32;
                        d[16] = (u64)(s64)SI(0x60) | (u64)((s64)SI(0x64) << 16) | (u64)((s64)SI(0x68) << 32);
                        d[17] = 0;
                        d += 18;
                        if (lit) {
                            d[0] = 0x1000000000008002ULL; d[1] = 0xE;
                            d[2] = *(u64 *)(texB + 0x30) | ((u64)*(u32 *)(texB + 0x24) << 37) |
                                   *(u32 *)(texB + 0x20) | 0x400000000ULL;
                            d[3] = 7;
                            d[4] = 0x25B; d[5] = 0;
                            d[6] = 0x3400000000008003ULL; d[7] = 0x521;
                            d[8] = *(u64 *)(sp + 0xD8);
                            d[9] = (u64)SU(0xA0) | (u64)SU(0xA4) << 32;
                            d[10] = (u64)(s64)SI(0x40) | (u64)((s64)SI(0x44) << 16) | (u64)((s64)SI(0x48) << 32);
                            d[11] = *(u64 *)(sp + 0xE8);
                            d[12] = (u64)SU(0xB0) | (u64)SU(0xB4) << 32;
                            d[13] = (u64)(s64)SI(0x50) | (u64)((s64)SI(0x54) << 16) | (u64)((s64)SI(0x58) << 32);
                            d[14] = *(u64 *)(sp + 0xF8);
                            d[15] = (u64)SU(0xC0) | (u64)SU(0xC4) << 32;
                            d[16] = (u64)(s64)SI(0x60) | (u64)((s64)SI(0x64) << 16) | (u64)((s64)SI(0x68) << 32);
                            d[17] = 0;
                            d += 18;
                        }
                    }
                }
            }
            remaining--;
            Dma_EndDirect(d);
            list += 0x18;
        } while (remaining != 0);
    }
    d = Dma_BeginDirect();
    d = EftBurst_PutModelEnvEnd(d);
    Dma_EndDirect(d);
}
