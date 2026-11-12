#include "common.h"

extern u8 *gEftSurf;
extern u8 *gBtlCamView;
extern f32 D_003842C4;
extern f32 D_003842C8;
extern f32 D_003842CC;
extern f32 D_003842D0;
extern f32 D_003842D4;

f32 EftStage_GetTintScale(void);
void EftSurf_DrawReflectTri(void *arg0, void *arg1, void *arg2);
void EftSurf_DrawTri(void *arg0, s64 arg1);
void EftWater_GetSurfaceY(void *arg0);
void Vu0Screen_StoreMtx(void *arg0);
void func_00128EF0(s64 arg0);
void func_00128F08(void);
void func_00128F90(void *arg0);
void func_00129660(void *arg0, void *arg1, void *arg2, void *arg3);
void func_00129B58(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
f32 func_00129CD8(void *arg0, void *arg1);
f32 func_00129E80(void *arg0, void *arg1);
s32 func_0012B9B0(void);
void func_0012B9C0(void);
s32 func_00136758(void *arg0, void *arg1, void *arg2);
void func_00137540(s32 arg0, s32 arg1);
void func_00137728(s32 arg0);
void func_00137AB0(void *arg0, s64 arg1);
void func_00137E20(void *arg0, void *arg1, void *arg2);
void func_00137F58(void *arg0, s32 arg1, s32 arg2, s32 arg3, s64 arg4, s32 arg5);
void func_00138C90(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
void func_00139390(void *arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
void func_003126C8(void *arg0, void *arg1);
void func_00312FB0(f32 farg0, void *arg0, void *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
f32 sinf(f32 x);

#define SP_F32(o) (*(f32 *)(sp + (o)))
#define SP_S32(o) (*(s32 *)(sp + (o)))
#define SP_S64(o) (*(s64 *)(sp + (o)))
#define F32_AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(u8 **)((u8 *)(p) + (o)))

void func_00136A00(void) {
    s64 spbuf[0x340 / 8];
    u8 *sp = (u8 *)spbuf;
    u8 *s1g;
    u8 *v0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    u8 *pf;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    s32 fp;
    s32 sp274;
    s32 count;
    s32 outer;
    s32 vcount;
    s32 sp28C;
    s32 sp290;
    s32 sp298;
    s32 sp29C;
    s32 sp2A0;
    s32 sp2A4;
    s32 sp288;
    s32 k;
    s64 sp280;
    s64 a0reg;
    s32 a0v;

    f22 = 0.0f;
    f1 = 1.0f;
    f0 = F32_AT(gEftSurf + 0x240, 0x10B8);
    v0 = PTR_AT(gEftSurf, 4);
    f22 = f0 * f0;
    sp274 = S32_AT(v0, 0x14);
    count = S32_AT(v0, 0x18);
    f27 = f1 / f22;
    s7 = PTR_AT(v0, 0x1C);
    memset(sp + 0x210, 0, 0x10);
    func_0012B9C0();
    S32_AT(gEftSurf, 0x10) = func_0012B9B0();
    func_00129C28(sp + 0x200, gBtlCamView + 0x1F0);
    EftWater_GetSurfaceY(sp + 0x270);
    SP_F32(0x204) = SP_F32(0x270);
    f26 = EftStage_GetTintScale();
    func_00137540(0, 0);
    func_00312FB0(f26, sp + 0x260, gEftSurf + 0x12C0);
    s1g = gEftSurf + 0x240;
    SP_F32(0x26C) = F32_AT(s1g, 0x108C) * 0.0078125f;

    a0v = S32_AT(s1g, 0x1078);
    a0reg = 0;
    if (a0v != 0) {
        SP_S64(0x210) = *(s64 *)((u8 *)(u32)a0v + ((S32_AT(s1g, 0x1108) + S32_AT(s1g, 0x1110)) << 4));
        a0reg = *(s64 *)((u8 *)(u32)a0v + ((S32_AT(s1g, 0x110C) + S32_AT(s1g, 0x1110)) << 4));
        SP_S64(0x218) = a0reg;
    }
    func_00128EF0(a0reg);
    Vu0Screen_StoreMtx(sp);
    func_00128F90(sp);

    if (count > 0) {
        outer = count;
        do {
            sp280 = *(s64 *)((u8 *)(u32)(sp274 + (S32_AT(s7, 0) << 6)) + 0x28);
            fp = S32_AT(s7, 0x20);
            f21 = F32_AT(s7, 0x14);
            f25 = 1.0f;
            sp288 = S32_AT(s7, 0x1C);
            f23 = F32_AT(s7, 0x18);
            s5 = PTR_AT(s7, 0x8);
            vcount = S32_AT(s7, 0x4);

            if ((fp & 0x60) == 0 && func_00136758(sp, s7 + 0x30, s7 + 0x40) != 0) {
                if ((fp & 0x200) != 0) {
                    func_00129B58(sp + 0x1F0, s7 + 0x50, sp + 0x200);
                    f1 = func_00129CD8(sp + 0x1F0, sp + 0x1F0);
                    if (D_003842C4 < f1) {
                        goto next;
                    }
                    if (D_003842C8 < f1) {
                        f25 = 1.0f - ((f1 - D_003842C8) / D_003842CC);
                    }
                }

                sp290 = 1;
                if ((fp & 0x8) == 0) {
                    sp290 = (fp >> 3) & 2;
                }

                if (vcount > 0) {
                    sp2A0 = fp & 0x80;
                    f24 = D_003842D0;
                    sp29C = fp & 0xC00;
                    sp298 = fp & 0x800;
                    f20 = 1.0f;
                    s6 = sp + 0x40;
                    do {
                        s1 = s6;
                        s2 = s5;
                        s3 = s6 + 0x20;
                        pf = s6 + 0x14;
                        f0 = func_00129E80(s5, sp + 0x200);
                        SP_F32(0x220) = f0;
                        f0 = func_00129E80(s5 + 0x30, sp + 0x200);
                        SP_F32(0x224) = f0;
                        f0 = func_00129E80(s5 + 0x60, sp + 0x200);
                        SP_F32(0x228) = f0;
                        sp28C = 1;
                        sp2A4 = 0xC;

                        for (k = 0; k < 3; k++) {
                            func_00129660(s1, s2, s2 + 0x10, s2 + 0x20);
                            F32_AT(s1, 0xC) = 1.0f;
                            F32_AT(s1, 0x18) = 1.0f;
                            F32_AT(s1, 0x1C) = 1.0f;
                            if (sp2A0 != 0) {
                                if (F32_AT(pf, 0) < 0.5f) {
                                    f1 = F32_AT(pf, -4) + (sinf(f21) * f24);
                                } else {
                                    f1 = F32_AT(pf, -4) - (sinf(f21) * f24);
                                }
                                F32_AT(pf, -4) = f1;
                                F32_AT(pf, 0) = F32_AT(pf, 0) + f23;
                            } else if (sp298 != 0) {
                                f0 = 0.0f;
                                func_003126C8(s1 + 0x20, sp + 0x260);
                                F32_AT(pf, 0x18) = F32_AT(pf, 0x18) * F32_AT(s2, 0x2C);
                                f1 = SP_F32(0x220 + k * 4);
                                if (f22 < f1) {
                                    SP_F32(0x220 + k * 4) = f22;
                                    f1 = f22;
                                }
                                if (D_003842D4 < f1) {
                                    sp28C = 0;
                                }
                                f0 = 1.0f - (f1 * f27);
                                *(f32 *)(sp + 0x230 + sp2A4) = f0;
                                if (f20 < f0) {
                                    *(f32 *)(sp + 0x230 + sp2A4) = 1.0f;
                                } else if (f0 < 0.0f) {
                                    *(f32 *)(sp + 0x230 + sp2A4) = 0.0f;
                                }
                            } else {
                                F32_AT(pf, -4) = F32_AT(pf, -4) + f21;
                                F32_AT(pf, 0) = F32_AT(pf, 0) + f23;
                                F32_AT(pf, 0x18) = F32_AT(pf, 0x18) * f25;
                            }
                            func_00129BD0(s3, s3, f26);
                            s3 += 0x30;
                            pf += 0x30;
                            s2 += 0x30;
                            s1 += 0x30;
                            sp2A4 += 0x10;
                        }

                        if (sp29C == 0xC00) {
                            if (sp28C != 0) {
                                func_00137E20(s6, sp + 0x210, sp + 0x230);
                            } else {
                                EftSurf_DrawReflectTri(s6, sp + 0x210, sp + 0x230);
                            }
                        } else if ((fp & 0x400) != 0) {
                            if (sp28C != 0) {
                                func_00137AB0(s6, sp280);
                            } else {
                                EftSurf_DrawTri(s6, sp280);
                            }
                        } else if (sp298 != 0) {
                            if (sp28C != 0) {
                                func_00138C90(s6, 0, sp + 0x210, sp + 0x230, sp288);
                            } else {
                                func_00139390(s6, 0, sp + 0x210, sp + 0x230, sp288);
                            }
                        } else {
                            func_00137F58(s6, sp290, 1, 0, sp280, sp288);
                        }
                        s5 += 0x90;
                        vcount -= 1;
                    } while (vcount != 0);
                }
            }
        next:
            s7 += 0x60;
            outer -= 1;
        } while (outer != 0);
    }
    func_00137728(0);
    func_00128F08();
}
