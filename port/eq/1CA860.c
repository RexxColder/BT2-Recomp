#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define FLDU16(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define FLD64(p, off) (*(s64 *)((u8 *)(p) + (off)))

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;
extern u8 *gEftMod1CBMgr;

void func_001CA5D8(void *arg0, void *arg1, void *arg2, void *arg3, f32 farg0);
void func_00129440(void *arg0, void *arg1, s32 arg2);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129D40(void *arg0, void *arg1, s64 arg2, s64 arg3);

/* packs a 24-bit value into bits 32..55 of the s64 at p+off, top byte forced to 0xFF */
#define PACK_COL(p, off, w) do { \
        s64 _v = FLD64(p, off); \
        _v = (_v & 0xFF000000FFFFFFFFLL) | ((s64)((w) & 0xFFFFFF) << 32); \
        FLD64(p, off) = _v; \
        ((u8 *)(p))[(off) + 7] = 0xFF; \
    } while (0)

void func_001CA860(void **arg0, void *arg1) {
    u8 spb[0x150];
    u8 *sp = spb;
    u8 *M = (u8 *)arg1;
    u8 *mgr;
    u8 *s4;
    u8 *s3;
    u8 *s0;
    u8 *e1;
    s32 s5;
    s32 s6;
    s32 s2;
    s32 w;
    s32 sum;
    s32 idx;
    s32 a0v;
    s32 X;
    f32 f0;
    f32 f12;

    if (FLD(M, 0x34) == 0) {
        mgr = gEftMod1CBMgr;
        FLD64(sp, 0xE0) = FLD64(mgr + FLD(M, 4) * 16, 0x38);
        FLD64(sp, 0xE8) = FLD64(mgr, 0x168);
    } else {
        u8 *b = (u8 *)FLD(M, 0x34);
        s32 o = FLD(M, 0x30) * 16;
        FLD64(sp, 0xE0) = FLD64(b + o, 0);
        FLD64(sp, 0xE8) = FLD64(b + o, 0x10);
    }

    s4 = (u8 *)*arg0;
    while (s4 != NULL) {
        if (FLD(s4, 0) != 0) {
            func_001CA5D8(sp, s4 + 0x60, s4 + 0x70, s4 + 0x50, 0.0f); /* f12: dead pass-through slot (only reaches a dot product that ignores it) */
            s6 = 0;
            s5 = 0;
            s3 = s4 + 0xB0;
            while (s5 < 4) {
                func_00129C50(sp + 0x40, sp, s3);
                s2 = s5 * 16;
                func_00129440(sp + 0x90 + s2, sp + 0x40, 1);
                s5 += 1;
                s3 += 0x10;
                w = FLD(sp + 0x90 + s2, 0);
                if (0xFFF0 < (u32)w) {
                    s6 = 1;
                    break;
                }
                if (0xFFF0 < (u32)FLD(sp + 0x90 + s2, 4)) {
                    s6 = 1;
                    break;
                }
                if (FLD(sp + 0x90 + s2, 8) < 0) {
                    s6 = 1;
                    break;
                }
                f0 = (f32)FLD(sp + 0x9C + s2, 0);
                f12 = 1.0f / f0;
                mgr = gEftMod1CBMgr;
                if (FLD(s4, 0) & 8) {
                    func_00129BD0(sp + 0x50 + s2, FLD(mgr, 0x270) + s2 + 0xC0, f12);
                } else {
                    func_00129BD0(sp + 0x50 + s2, FLD(mgr, 0x270) + s2 + 0x80, f12);
                }
            }

            if (s6 == 0) {
                s0 = D_00387AD8;
                D_00387AD8 = s0 + 0x90;
                if (s0 == NULL) {
                    return;
                }
                FLD(s0, 0x20) = 0x5C;
                FLD64(s0, 0x00) = ((s64)0xA000 << 16) | 8;
                FLD64(s0, 0x10) = ((s64)0xE4000000 << 32) | 0x8001;
                FLD64(s0, 0x18) = ((((s64)0x421421 << 16) | 0x4214) << 16) | 0x2160;
                func_00129D40(sp + 0xD0, s4 + 0x80, ((s64)0xE4000000 << 32) | 0x8001,
                              ((((s64)0x421421 << 16) | 0x4214) << 16) | 0x2160);

                s0[0x30] = sp[0xD0];
                s0[0x31] = sp[0xD4];
                s0[0x32] = sp[0xD8];
                s0[0x33] = sp[0xDC];
                FLDF(s0, 0x34) = FLDF(sp, 0x58);
                s0[0x48] = sp[0xD0];
                s0[0x49] = sp[0xD4];
                s0[0x4A] = sp[0xD8];
                s0[0x4B] = sp[0xDC];
                FLDF(s0, 0x4C) = FLDF(sp, 0x68);
                s0[0x60] = sp[0xD0];
                s0[0x61] = sp[0xD4];
                s0[0x62] = sp[0xD8];
                s0[0x63] = sp[0xDC];
                FLDF(s0, 0x64) = FLDF(sp, 0x78);
                s0[0x78] = sp[0xD0];
                s0[0x79] = sp[0xD4];
                s0[0x7A] = sp[0xD8];
                s0[0x7B] = sp[0xDC];
                FLDF(s0, 0x7C) = FLDF(sp, 0x88);
                FLDF(s0, 0x38) = FLDF(sp, 0x50);
                FLDF(s0, 0x3C) = FLDF(sp, 0x54);
                FLDF(s0, 0x50) = FLDF(sp, 0x60);
                FLDF(s0, 0x54) = FLDF(sp, 0x64);
                FLDF(s0, 0x68) = FLDF(sp, 0x70);
                FLDF(s0, 0x6C) = FLDF(sp, 0x74);
                FLDF(s0, 0x80) = FLDF(sp, 0x80);
                FLDF(s0, 0x84) = FLDF(sp, 0x84);

                FLDU16(s0, 0x40) = FLDU16(sp, 0x90);
                FLDU16(s0, 0x42) = FLDU16(sp, 0x94);
                PACK_COL(s0, 0x40, FLD(sp, 0x98));
                FLDU16(s0, 0x58) = FLDU16(sp, 0xA0);
                FLDU16(s0, 0x5A) = FLDU16(sp, 0xA4);
                PACK_COL(s0, 0x58, FLD(sp, 0xA8));
                FLDU16(s0, 0x70) = FLDU16(sp, 0xB0);
                FLDU16(s0, 0x72) = FLDU16(sp, 0xB4);
                PACK_COL(s0, 0x70, FLD(sp, 0xB8));
                FLDU16(s0, 0x88) = FLDU16(sp, 0xC0);
                FLDU16(s0, 0x8A) = FLDU16(sp, 0xC4);
                PACK_COL(s0, 0x88, FLD(sp, 0xC8));
                FLD64(s0, 0x28) = FLD64(sp, 0xE0 + 8 * FLD(s4, 4));

                sum = (FLD(sp, 0x98) + FLD(sp, 0xC8)) + (FLD(sp, 0xB8) + FLD(sp, 0xA8));
                sum = sum >> 10;
                a0v = FLD(s4, 8);
                if (sum >= 0) {
                    if (sum < 0x1000) {
                        e1 = D_00387AE0 + (2 * sum + a0v) * 8;
                    } else {
                        e1 = D_00387AE0 + a0v * 8 + 0xFFF0;
                    }
                } else {
                    e1 = D_00387AE0 + a0v * 8;
                }
                X = FLD(e1, 4);
                FLD(X, 4) = (s32)s0;
                FLD(e1, 4) = (s32)s0;
            }
        }
        s4 = (u8 *)FLD(s4, 0x130);
    }
    return;
}
