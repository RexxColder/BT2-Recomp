#include "common.h"

#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x)                                                                                \
    do {                                                                                               \
        (out) = (s32)(x);                                                                              \
    } while (0)

void ColSeg_Set(void *, void *, void *);
s32 func_002745F8(s32);
s32 func_0011E1C8(void *);
void *func_0011E310(void);
f32 func_00273000(void);
f32 func_00273048(void);
void sceVu0InterVector(f32, void *, void *, void *);
void func_003126C8(void *, void *);

void func_001240F0(void *arg0) {
    u8 sp[0x30];
    u8 *st;
    u8 *s0;
    u8 *s1;
    u8 *a1;
    u8 *a2;
    void *p1;
    void *p2;
    void *p3;
    s32 n;
    s32 s3;
    s32 s5;
    s32 r;
    s32 v;
    f32 f20;
    f32 f21;

    st = (u8 *)arg0 + 0xBE0;
    if (S32AT(arg0, 0xBE4) <= 0) {
        return;
    }
    if (S32AT(st, 4) > 0) {
        s0 = (u8 *)arg0 + 0xFA0;
        s3 = 0;
        do {
            v = *(s8 *)(s0 - 0x100);
            if (v >= 0 && func_002745F8(v) != 0) {
                *(s8 *)(s0 - 0x100) = -1;
                *s0 = *s0 | 1;
                S32AT(st, 8) = 0;
            }
            v = *(s8 *)(s0 - 0x120);
            if (v >= 0 && func_002745F8(v) != 0) {
                *(s8 *)(s0 - 0x120) = -1;
                *s0 = *s0 | 2;
                S32AT(st, 8) = 0;
            }
            v = *(s8 *)(s0 - 0x20);
            if (v >= 0 && func_002745F8(v) != 0) {
                *(s8 *)(s0 - 0x20) = -1;
                *s0 = *s0 | 4;
                S32AT(st, 8) = 0;
            }
            s3 += 1;
            s0 += 1;
        } while (s3 < S32AT(st, 4));
    }

    if (S32AT(st, 8) != 0) {
        return;
    }
    S32AT(st, 8) = 1;
    s3 = 0;
    f21 = func_00273000();
    f20 = func_00273048();
    n = S32AT(st, 4);
    if (n <= 0) {
        return;
    }
    CVT_W_S(s5, f20);
    s0 = st + 0x3C0;
    s1 = st + 0x260;
    a1 = (u8 *)arg0 + 0xC00;
    a2 = st;

    do {
        if (*s0 & 1) {
            ColSeg_Set(sp, a1, a1);
            F32AT(sp, 0x14) = f20;
            if (func_0011E1C8(sp) == 0) {
                *(s16 *)(s1 - 0x40) = (s16)s5;
                *(s8 *)(s0 - 0x100) = -1;
            } else {
                p1 = func_0011E310();
                CVT_W_S(r, F32AT(p1, 0x14));
                *(s16 *)(s1 - 0x40) = (s16)r;
                p2 = func_0011E310();
                if (S32AT(p2, 0x20) & 0x40000000) {
                    p3 = func_0011E310();
                    *(u8 *)(s0 - 0x100) = *((u8 *)p3 + 0x40);
                } else {
                    *(s8 *)(s0 - 0x100) = -1;
                }
            }
            *s0 = *s0 & 0xFE;
            S32AT(st, 8) = 0;
            return;
        }
        if ((*s0 & 4) && s3 > 0) {
            sceVu0InterVector(0.5f, sp, a1, a2 + 0x10);
            func_003126C8(sp + 0x10, sp);
            F32AT(sp, 0x14) = f20;
            F32AT(sp, 0x1C) = 1.0f;
            F32AT(sp, 0x0C) = 1.0f;
            if (func_0011E1C8(sp) == 0) {
                *(s16 *)(s1 + 0x100) = (s16)s5;
                *(s8 *)(s0 - 0x20) = -1;
            } else {
                p1 = func_0011E310();
                CVT_W_S(r, F32AT(p1, 0x14));
                *(s16 *)(s1 + 0x100) = (s16)r;
                p2 = func_0011E310();
                if (S32AT(p2, 0x20) & 0x40000000) {
                    p3 = func_0011E310();
                    *(u8 *)(s0 - 0x20) = *((u8 *)p3 + 0x40);
                } else {
                    *(s8 *)(s0 - 0x20) = -1;
                }
            }
            *s0 = *s0 & 0xFB;
            S32AT(st, 8) = 0;
            return;
        }
        if (*s0 & 2) {
            ColSeg_Set(sp, a1, a1);
            F32AT(sp, 0x14) = f21;
            if (func_0011E1C8(sp) != 0) {
                p1 = func_0011E310();
                CVT_W_S(r, F32AT(p1, 0x14));
                *(s16 *)(s1) = (s16)r;
                p2 = func_0011E310();
                if (S32AT(p2, 0x20) & 0x40000000) {
                    p3 = func_0011E310();
                    *(u8 *)(s0 - 0x120) = *((u8 *)p3 + 0x40);
                } else {
                    *(s8 *)(s0 - 0x120) = -1;
                }
            } else {
                CVT_W_S(r, f21);
                *(s16 *)(s1) = (s16)r;
                *(s8 *)(s0 - 0x120) = -1;
            }
            *s0 = *s0 & 0xFD;
            S32AT(st, 8) = 0;
            return;
        }
        s3 += 1;
        s0 += 1;
        s1 += 2;
        a1 += 0x10;
        a2 += 0x10;
    } while (s3 < n);
}
