#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

f32 cosf(f32 arg0);
f32 sinf(f32 arg0);
void Mtx_StoreIdentity(void *arg0);
void Vec3_Add(void *arg0, void *arg1, void *arg2);
void Vec3_Cross(void *arg0, void *arg1, void *arg2);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg0, void *arg1, f32 farg0);
void func_00129C38(void *arg0, void *arg1);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00208F18(s32 arg0, void *arg1, s32 arg2);

void func_001DC5C0(void *arg0) {
    u8 spb[0x110];
    u8 *sp = spb;
    u8 *sp60 = sp + 0x60;
    u8 *T;
    u8 *s7;
    u8 *s6;
    u8 *s5;
    u8 *s3;
    u8 *s2;
    u8 *s0p;
    u8 *s1p;
    u8 *s3p2;
    s32 fp;
    s32 s0v;
    s32 s3v;

    fp = 0;
    T = (u8 *)FLD(arg0, 0x38);
    s6 = T + 0x230;
    s7 = (u8 *)FLD(T, 0);
    s2 = T;
    func_00208F18(FLD(T, 0x244), sp60, 0x2F);
    FLDF(T, 0x23C) = 1.0f;
    func_00129C50(s6, sp60, s7 + 0x100);
    s5 = s7 + 0x10;
    s3 = s7 + 0x1C;
    do {
        if (FLD(T, 0x240) != fp) {
            s0p = s2 + 0x50;
            FLDF(s3, 0) = 1.0f;
            s1p = s2 + 0x140;
            func_00129C50(s0p, sp60, s5);
            Vec3_Sub(s1p, s0p, s6);
            Vec3_Normalize(s1p, s1p);
        }
        fp += 1;
        s5 += 0x10;
        s3 += 0x10;
        s2 += 0x10;
    } while (fp < 7);

    func_00208DE8(FLD(T, 0x244), sp + 0x40, 0x11);
    func_00208DE8(FLD(T, 0x244), sp + 0x50, 0x2E);
    fp = 7;
    s6 = T + 0x1B0;
    s5 = T + 0xC0;
    Vec3_Sub(sp + 0x10, sp + 0x50, sp + 0x40);
    Vec3_Normalize(sp + 0x10, sp + 0x10);
    func_00208DE8(FLD(T, 0x244), sp + 0x40, 0x13);
    func_00208DE8(FLD(T, 0x244), sp + 0x50, 0x21);
    Vec3_Sub(sp, sp + 0x50, sp + 0x40);
    Vec3_Normalize(sp, sp);
    Vec3_Cross(sp + 0x20, sp, sp + 0x10);

    /* loop 2: fp = 7 */
    do {
        if (FLD(T, 0x240) != fp) {
            s3v = fp * 16 + 0x10;
            s0v = fp * 16 + 0x140;
            Mtx_StoreIdentity(sp60);
            s1p = s7 + 0xC + s3v;
            s2 = T + 4 + s0v;
            FLDF(s6, 0) = cosf(FLDF(s1p, 0));
            FLDF(s2, 0) = sinf(FLDF(s1p, 0));
            s0p = T + s0v;
            FLD(s0p, 8) = 0;
            FLDF(s0p, 0xC) = 1.0f;
            func_00129C38(sp60, sp);
            func_00129C38(sp + 0x70, sp + 0x10);
            func_00129C38(sp + 0x80, sp + 0x20);
            func_00129C50(s6, sp60, s6);
            func_00129BD0(sp + 0x30, sp, FLDF(s7 + s3v, 0));
            Vec3_Add(s5, sp + 0x40, sp + 0x30);
            func_00129BD0(sp + 0x30, sp + 0x10, FLDF(s7 + s3v, 4));
            s3p2 = s7 + s3v;
            Vec3_Add(s5, s5, sp + 0x30);
            func_00129BD0(sp + 0x30, sp + 0x20, FLDF(s3p2, 8));
            Vec3_Add(s5, s5, sp + 0x30);
        }
        fp += 1;
        s6 += 0x10;
        s5 += 0x10;
    } while (fp < 8);

    func_00208DE8(FLD(T, 0x244), sp + 0x40, 0x21);
    func_00208DE8(FLD(T, 0x244), sp + 0x50, 0x13);
    fp = 8;
    s6 = T + 0x1C0;
    s5 = T + 0xD0;
    Vec3_Sub(sp, sp + 0x50, sp + 0x40);
    Vec3_Normalize(sp, sp);
    Vec3_Cross(sp + 0x20, sp, sp + 0x10);

    /* loop 3: fp = 8 */
    do {
        if (FLD(T, 0x240) != fp) {
            s3v = fp * 16 + 0x10;
            s0v = fp * 16 + 0x140;
            Mtx_StoreIdentity(sp60);
            s1p = s7 + 0xC + s3v;
            s2 = T + 4 + s0v;
            FLDF(s6, 0) = cosf(FLDF(s1p, 0));
            FLDF(s2, 0) = sinf(FLDF(s1p, 0));
            s0p = T + s0v;
            FLD(s0p, 8) = 0;
            FLDF(s0p, 0xC) = 1.0f;
            func_00129C38(sp60, sp);
            func_00129C38(sp + 0x70, sp + 0x10);
            func_00129C38(sp + 0x80, sp + 0x20);
            func_00129C50(s6, sp60, s6);
            func_00129BD0(sp + 0x30, sp, FLDF(s7 + s3v, 0));
            Vec3_Add(s5, sp + 0x40, sp + 0x30);
            func_00129BD0(sp + 0x30, sp + 0x10, FLDF(s7 + s3v, 4));
            s3p2 = s7 + s3v;
            Vec3_Add(s5, s5, sp + 0x30);
            func_00129BD0(sp + 0x30, sp + 0x20, FLDF(s3p2, 8));
            Vec3_Add(s5, s5, sp + 0x30);
        }
        fp += 1;
        s6 += 0x10;
        s5 += 0x10;
    } while (fp < 9);
    return;
}
