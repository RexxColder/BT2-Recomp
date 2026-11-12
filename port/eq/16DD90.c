#include "common.h"

#define OBJW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define OBJF(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define OBJP(p, o) (*(u8 **)((u8 *)(p) + (o)))
#define SPF(o) (*(f32 *)(fr + (o)))
#define SPA(o) ((void *)(fr + (o)))

extern f32 D_00384890;
extern f32 D_00384894;

f32 BtlCharApi_GetHeight(void *arg0);
s32 EftShot_TestBits(void *arg0, s32 arg1);
void Vec3_Normalize(void *arg0, void *arg1);
void Vec3_Sub(void *arg0, void *arg1, void *arg2);
void func_00129BD0(void *arg1, void *arg2, f32 farg0);
void func_00129C28(void *arg0, void *arg1);
void func_0012A360(f32 farg0, void *arg1, void *arg2, void *arg3);
void func_0016DB58(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, f32 farg0, f32 farg1, f32 farg2);
void func_00191688(void *arg0);
void func_001917B0(void *arg0, s32 arg1, void *arg2);
void func_00191838(void *arg0, void *arg1);
void func_00191890(void *arg0, s32 arg1);
void func_0019F3B0(void *arg0, void *arg1);
void func_00208DE8(void *arg0, void *arg1, s32 arg2);
void *func_0020B3D0(void *arg0);
s32 rand(void);

void func_0016DD90(u8 *obj) {
    u8 fr[0x40] __attribute__((aligned(8)));
    u8 *s3;
    u8 *s5;
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *np;
    u8 *t;
    void *s7;
    s32 s2;
    s32 v;
    s32 v1;
    s32 rA;
    s32 rB;
    f32 f0;
    f32 f20;
    f32 f21;

    s3 = OBJP(obj, 0x38);
    s5 = OBJP(s3, 0xB0);
    s7 = func_0020B3D0(OBJP(s5, 0));
    if (EftShot_TestBits(OBJP(s5, 0), 4) != 0) {
        func_0016DB58(obj, 4, 2, 1, 0, 0.0f, OBJF(s3, 0x1C), OBJF(s3, 0x18));
    }

    /* loop 1: 14 effect slots, timers and a one-shot flag */
    f21 = 8.0f;
    f20 = 1.0f;
    s0 = s3 + 0xAC0;
    s2 = 0xD;
    do {
        if (OBJP(s0, 0x20) != NULL) {
            if (!(OBJW(s0, 0) & 1)) {
                f0 = OBJF(s0, 4);
                if (!(f21 <= f0)) {
                    OBJF(s0, 4) = f0 + f20;
                } else {
                    func_00191890(OBJP(s0, 0x20), 1);
                    OBJW(s0, 0) = OBJW(s0, 0) | 1;
                }
            }
        }
        s2 -= 1;
        s0 += 0x30;
    } while (s2 >= 0);

    if (!(OBJW(s3, 0) & 0x200)) {
        if (EftShot_TestBits(OBJP(s5, 0), 0x40) != 0) {
            OBJW(s3, 0) = OBJW(s3, 0) | 0x200;
        }
    } else {
        func_00208DE8(OBJP(s5, 0), SPA(0x10), 0x11);
        func_00208DE8(s7, SPA(0x20), 3);

        /* loop 2: the 14 slots of s3 (stride 0x30), each one steered toward s5's target */
        s2 = 0;
        s1 = s3;
        do {
            s4 = s1 + 0xAC0;
            v = OBJW(s4, 0);
            if (((v & 2) != 0) && ((v & 4) == 0)) {
                if (!(OBJF(s1, 0xAC8) >= 6.0f)) {
                    func_00129C28(SPA(0), SPA(0x20));
                    t = s1 + 0xAD0;
                    SPF(4) = SPF(4) + OBJF(s1, 0xACC);
                    Vec3_Sub(SPA(0), SPA(0), t);
                    func_0012A360(OBJF(s1, 0xAC8) / 6.0f, SPA(0), SPA(0), t);
                    func_001917B0(OBJP(s1, 0xAE0), 1, SPA(0));
                } else {
                    func_00191688(OBJP(s1, 0xAE0));
                    func_00129C28(SPA(0), SPA(0x20));
                    SPF(4) = SPF(4) + OBJF(s1, 0xACC);
                    if ((s2 & 1) == 0) {
                        func_0019F3B0(SPA(0), OBJP(OBJP(s5, 0x20), 0xC));
                    }
                    OBJW(s4, 0) = OBJW(s4, 0) | 4;
                }
                OBJF(s1, 0xAC8) = OBJF(s1, 0xAC8) + 1.0f;
            }
            s2 += 1;
            s1 += 0x30;
        } while (s2 < 0xE);

        /* spawn one new slot when there is room */
        v1 = OBJW(s3, 0xAB0);
        if (v1 < 0xE) {
            np = s3 + ((v1 * 3) << 4);
            s4 = np + 0xAC0;
            f20 = BtlCharApi_GetHeight(s7) / D_00384890;
            rA = rand();
            rB = rand();
            OBJW(s4, 0) = OBJW(s4, 0) | 2;
            OBJF(s4, 0xC) = ((((f32)rA / D_00384894) - ((f32)rB / D_00384894)) * f20) * 10.0f;
            OBJW(s3, 0xAB0) = OBJW(s3, 0xAB0) + 1;
        }

        if (!(OBJW(s3, 0) & 0x400)) {
            if (EftShot_TestBits(OBJP(s5, 0), 0x40) != 0) {
                OBJW(s3, 0xAB0) = 0;
                f20 = 1.0f;
                func_00129C28(SPA(0), SPA(0x10));
                t = fr + 0x30;
                SPF(4) = SPF(0x24);
                Vec3_Sub(t, SPA(0x20), SPA(0));
                Vec3_Normalize(t, t);
                SPF(0x24) = SPF(0x24) + OBJF(s4, 0xC);

                /* loop 3: sweep the 14 slots along the normalized vector */
                s1 = s3;
                s2 = 0xD;
                do {
                    s2 -= 1;
                    func_00191838(OBJP(s1, 0xAE0), t);
                    func_00191890(OBJP(s1, 0xAE0), 0);
                    func_00129BD0(SPA(0), t, 80.0f);
                    Vec3_Sub(SPA(0), SPA(0x20), SPA(0));
                    SPF(0xC) = f20;
                    func_001917B0(OBJP(s1, 0xAE0), 1, SPA(0));
                    func_00129C28(s1 + 0xAD0, SPA(0));
                    s1 += 0x30;
                } while (s2 >= 0);
                OBJW(s3, 0) = OBJW(s3, 0) | 0x400;
            }
            OBJF(s3, 0xD60) = OBJF(s3, 0xD60) + 1.0f;
        }
    }
}
