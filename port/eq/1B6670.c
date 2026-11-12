#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FW(p, o) (*(f32 *)((u8 *)(p) + (o)))

extern u8 D_0036EC20[] __attribute__((section(".data")));
extern u8 D_0036EC24[] __attribute__((section(".data")));
extern u8 D_0036EC2C[] __attribute__((section(".data")));
extern f32 D_00384FF4;
extern f32 D_00384FF8;
extern f32 D_00384FFC;
extern f32 D_00385000;
extern f32 D_00385004;

s32 rand(void);
f32 BtlCharApi_GetHeight(void *arg0, f32 farg0);
void func_00208DE8(void *arg0, void *arg1, s32 arg2);
void func_003126C8(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
f32 func_001B7788(void *arg0);
void func_00312FB0(f32 farg0, void *arg1, void *arg2);
void func_00312680(f32 farg0, void *arg1, void *arg2);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
f32 EftMath_WrapAngle(f32 farg0, s32 *arg1);
void func_001B5A70(f32 f0, f32 f1, f32 f2, f32 f3, f32 f4, f32 f5, f32 f6, void *arg0, void *arg1, s32 a2, s32 a3, s32 t0);

/* cvt.w.s: truncates toward zero-even, written out (FCSR RN) */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(x, out) do { \
    (out) = (s32)(x); \
} while (0)

void func_001B6670(void *arg0, f32 farg0) {
    f32 V0[4];
    f32 V10[4];
    f32 V20[4];
    f32 V30[4];
    f32 V40[4];
    u32 sp50;
    s32 sp54;
    s32 sp58;
    u8 *p5C;
    s32 sp60;
    s32 sp64;
    s32 fp;
    s32 s1;
    s32 s1o;
    s32 cnt;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 m;
    u8 *s3;
    f32 f0;
    f32 f5;
    f32 f6;
    f32 f12;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 f24;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f29;
    f32 f30;
    f32 e2c;
    f32 e20;
    f32 h1;
    f32 h2;
    f32 lim;
    f32 rr;
    f32 ang;
    s32 tmp;

    /* first BtlCharApi_GetHeight: arg0 and f12 pass through (nothing set them before the jal) */
    f30 = BtlCharApi_GetHeight(arg0, farg0) * D_00384FF4;
    f30 = f30 * 5.0f;
    sp50 = 0;
    p5C = D_0036EC20;
    if (W(p5C, 0) != 4) {
        sp60 = 0x10;
        sp64 = 0;
        do {
            func_00208DE8(arg0, V0, W(p5C, 0));
            func_003126C8(V10, V0);
            tmp = W(D_0036EC24, sp64);
            if (tmp >= 0) {
                func_00208DE8(arg0, V30, tmp);
                func_00312650(V30, V30, V0);
                rr = func_001B7788(V30);
                lim = FW(p5C, 8);
                if (lim < rr) {
                    f0 = (rr / lim) + 1.0f;
                    CVT_W_S(f0, sp54);
                    func_00312FB0(1.0f / (f32)sp54, V20, V30);
                } else {
                    V20[0] = 0.0f;
                    sp54 = 1;
                    V20[1] = 0.0f;
                    V20[2] = 0.0f;
                    V20[3] = 1.0f;
                }
            } else {
                V20[0] = 0.0f;
                sp54 = 1;
                V20[1] = 0.0f;
                V20[2] = 0.0f;
                V20[3] = 1.0f;
            }

            if (sp54 > 0) {
                fp = 0;
                sp58 = sp64;
                f29 = D_00384FF8;
                do {
                    s3 = D_0036EC24 + sp60;
                    f0 = (f32)W(s3, 0);
                    f27 = f29 / f0;
                    s1 = 0;
                    r1 = rand();
                    f6 = (f32)r1;
                    f6 = f6 / D_00384FFC;
                    cnt = W(s3, 0);
                    f0 = (f32)fp;
                    f5 = f0 * V20[0];
                    f12 = f0 * V20[2];
                    f0 = f0 * V20[1];
                    V0[0] = V10[0] + f5;
                    V0[2] = V10[2] + f12;
                    V0[1] = V10[1] + f0;
                    f26 = f6 * f29;
                    if (cnt > 0) {
                        f23 = D_00384FFC;
                        f24 = 0.0f;
                        f25 = D_00385000;
                        do {
                            r1 = rand();
                            h1 = ((f32 (*)(void *))BtlCharApi_GetHeight)(arg0) * f25;
                            e2c = FW(D_0036EC2C + sp58, 0);
                            f22 = (((f32)r1 / f23) + e2c) * h1;
                            r2 = rand();
                            f21 = (f32)r2;
                            h2 = ((f32 (*)(void *))BtlCharApi_GetHeight)(arg0) * f25;
                            s1o = s1;
                            s1 = s1 + 1;
                            f12 = (f32)s1o * f27;
                            ang = f26 + f12;
                            e20 = FW(D_0036EC20 + sp60, 0);
                            f21 = ((f21 / f23) * 0.5f + e20) * h2;
                            f20 = EftMath_WrapAngle(ang, (s32 *)D_0036EC20);
                            FW(V40, 0) = func_0012A3F8(f20);
                            FW(V40, 4) = Mathf_Cos(f20);
                            W(V40, 8) = 0;
                            FW(V40, 0xC) = 1.0f;
                            func_00312680(f21 * 1.5f, V40, V40);
                            r3 = rand();
                            m = 0x50 - (r3 % 16);
                            func_001B5A70(f30, f22 + f22, f24, f24, D_00385004, (f32)m, farg0, V0, V40, 0, 0, 0x12);
                        } while (s1 < W(s3, 0));
                    }
                    fp += 1;
                } while (fp < sp54);
            }

            sp50 += 1;
            p5C += 0x18;
            sp60 += 0x18;
            sp64 += 0x18;
        } while (sp50 < 0x17 && W(p5C, 0) != 4);
    }
}
