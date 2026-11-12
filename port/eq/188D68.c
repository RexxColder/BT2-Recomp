#include "common.h"

f32 Rand_FloatRange(f32 farg0, f32 farg1);
void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
void func_00129C28(s32 arg0, s32 arg1);
f32 func_00188F78(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001890F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00189EB8(s32 arg0, s32 arg1, s32 arg2);
void func_00189EE8(s32 arg0, s32 arg1, s32 arg2);
void *func_00189F50(void);

s32 func_00188D68(u8 *arg0) {
    u8 sp[0x30];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s5;
    s32 s6;
    s32 s7;
    s32 t;
    s32 rnd;
    s32 v;
    f32 f20;
    f32 f21;
    f32 f12;
    f32 f13;

    s3 = arg0;
    s6 = 0;
    s4 = *(u8 **)(s3 + 0x30);
    f21 = *(f32 *)(s3 + 0xC4) / *(f32 *)(s3 + 0xB4);
    s7 = *(s32 *)(s3 + 0x34);
    s2 = *(u8 **)(s3 + 0x1E0);
    if (f21 < 1.0f) {
        return 0;
    }
    /* cvt.w.s: truncates toward zero */
    t = (s32)f21;
    rnd = t;

    while (s6 < rnd) {
        f20 = (f32)s6;
        s1 = sp + 0x20;
        s5 = s3 + 0x70;
        func_00129BD0((s32)s1, (s32)s5, *(f32 *)(s3 + 0xB4) * f20);
        f12 = Rand_FloatRange(*(f32 *)(s4 + 0x98), *(f32 *)(s4 + 0x9C));
        s0 = sp + 0x10;
        func_00129BD0((s32)s0, (s32)s5, f12);
        Vec3_Add((s32)s1, (s32)s1, (s32)s0);
        Vec3_Add((s32)sp, (s32)(s3 + 0x50), (s32)s1);
        if (s2 != 0) {
            if (*(u16 *)(s2 + 0xBE) & 2) {
                s2 = *(u8 **)(s2 + 0xC0);
                s6 += 1;
                continue;
            }
            if (*(s32 *)(s4 + 0xA4) & 0x4000) {
                func_00129C28((s32)sp, (s32)s2);
            }
            s0 = s2;
        } else {
            s0 = (u8 *)func_00189F50();
            if (s0 == 0) {
                break;
            }
            s2 = s0;
            func_00189EB8((s32)(s3 + 0x1E0), (s32)(s3 + 0x1E4), (s32)s0);
        }
        func_001890F8((s32)s0, (s32)s4, s7, (s32)s3[0x1D5], (s32)s3[0x1D4]);
        f12 = *(f32 *)(s3 + 0x88) * *(f32 *)(s3 + 0x80);
        f13 = *(f32 *)(s4 + 0x20) * f20;
        func_00188F78(f12, f13, (s32)s0, (s32)s4, (s32)sp, (s32)s5);
        *(u16 *)(s0 + 0xBE) = (u16)(*(u16 *)(s0 + 0xBE) | 3);
        s2 = *(u8 **)(s2 + 0xC0);
        s6 += 1;
    }

    while (s2 != 0) {
        v = *(u16 *)(s2 + 0xBE);
        if (!(v & 2)) {
            *(u16 *)(s2 + 0xBE) = 0;
            func_00189EE8((s32)(s3 + 0x1E0), (s32)(s3 + 0x1E4), (s32)s2);
        }
        s2 = *(u8 **)(s2 + 0xC0);
    }
    return 1;
}
