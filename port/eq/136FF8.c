#include "common.h"

extern u8 *gEftSurf;
extern s32 gBtlCamView;
extern f32 D_003842D8;
extern f32 D_003842DC;
extern f32 D_003842E0;

void Mtx_InverseRT(u8 *arg0, s32 arg1);
void func_00129C28(u8 *arg0, u8 *arg1);
void func_0012B9C0(void);
s32 func_0012B9B0(void);
void Vu0Screen_StoreMtx(u8 *arg0);
void func_00128EF0(void);
void func_00128F90(u8 *arg0);
void func_00138548(s64 arg0, s32 arg1);
void func_00137540(s32 arg0, s32 arg1);
s32 func_00136758(u8 *arg0, u8 *arg1, u8 *arg2);
void func_00129B58(u8 *arg0, u8 *arg1, u8 *arg2);
f32 func_00129CD8(u8 *arg0, u8 *arg1);
void func_00137838(s64 arg0);
void func_00129660(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3);
void func_00129BD0(u8 *arg0, u8 *arg1, f32 farg0);
void func_00137AB0(u8 *arg0, s64 arg1);
void func_00137728(s32 arg0);
void func_00128F08(void);
s32 func_00276D00(void);

void func_00136FF8(void) {
    u8 sp[0x260];   /* tamano de locales del original (antes 0x250) */
    u8 *rec;
    u8 *tbl;
    u8 *s3;
    u8 *s5;
    u8 *s7;
    u8 *s1;
    u8 *a0p;
    u8 *a1p;
    s32 count;
    s32 fp;
    s32 flags;
    s32 s2;
    s32 s4;
    s32 s6;
    s64 sp258;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f20 = 1.0f;
    f32 f21;
    f32 f22;
    f32 f23;

    if (gEftSurf != NULL && func_00276D00() != 0) {
        rec = *(u8 **)(gEftSurf + 4);
        tbl = *(u8 **)(rec + 0x14);
        count = *(s32 *)(rec + 0x18);
        s3 = *(u8 **)(rec + 0x1C);
        if (gBtlCamView != 0) {
            Mtx_InverseRT(sp + 0x210, gBtlCamView);
            func_00129C28(sp + 0x200, sp + 0x240);
        }
        func_0012B9C0();
        *(s32 *)(gEftSurf + 0x10) = func_0012B9B0();
        Vu0Screen_StoreMtx(sp);
        func_00128EF0();
        func_00128F90(sp);
        func_00138548(1, 0);
        func_00137540(0, 1);
        if (count > 0) {
            do {
                f23 = *(f32 *)(s3 + 0x14);
                f22 = *(f32 *)(s3 + 0x18);
                f21 = 1.0f;
                sp258 = *(s64 *)(tbl + (*(s32 *)s3 << 6) + 0x28);
                flags = *(s32 *)(s3 + 0x20);
                s5 = *(u8 **)(s3 + 0x8);
                fp = *(s32 *)(s3 + 0x4);
                if (func_00136758(sp, s3 + 0x30, s3 + 0x40) != 0) {
                    func_00129B58(sp + 0x1F0, s3 + 0x50, sp + 0x200);
                    f1 = func_00129CD8(sp + 0x1F0, sp + 0x1F0);
                    if (!(D_003842D8 < f1)) {
                        if (D_003842DC < f1) {
                            f0 = f1 - D_003842DC;
                            f1 = D_003842E0;
                            f0 = f0 / f1;
                            f21 = f21 - f0;
                        }
                        if (flags & 0x8) {
                            func_00137838(1);
                        }
                        if (flags & 0x10) {
                            func_00137838(2);
                        }
                        s6 = 0;
                        if (fp > 0) {
                            s7 = sp + 0x40;
                            do {
                                s1 = s7 + 0x2C;
                                s2 = 0;
                                s4 = 2;
                                do {
                                    a0p = s7 + s2;
                                    a1p = a0p + 0x20;
                                    func_00129660(a0p, s5 + s2, s5 + s2 + 0x10, s5 + s2 + 0x20);
                                    *(f32 *)(s1 - 0x20) = f20;
                                    f1 = *(f32 *)(s1 - 0x1C) + f23;
                                    f2 = *(f32 *)(s1 - 0x18) + f22;
                                    *(f32 *)(s1 - 0x14) = f20;
                                    *(f32 *)(s1 - 0x10) = f20;
                                    f0 = *(f32 *)s1 * f21;
                                    s4 -= 1;
                                    *(f32 *)(s1 - 0x1C) = f1;
                                    s2 += 0x30;
                                    *(f32 *)(s1 - 0x18) = f2;
                                    *(f32 *)s1 = f0;
                                    s1 += 0x30;
                                    func_00129BD0(a1p, a1p, f20);
                                } while (s4 >= 0);
                                func_00137AB0(sp + 0x40, sp258);
                                s6 += 1;
                                s5 += 0x90;
                            } while (s6 < fp);
                        }
                    }
                }
                s3 += 0x60;
                count -= 1;
            } while (count != 0);
        }
        func_00137728(1);
        func_00128F08();
    }
}
