#include "common.h"

void func_001B9470(s32 arg0, s32 arg1, s32 arg2);
s32 rand(void);
extern f32 D_00385100;
extern u8 *gEftPtcl3Mgr;

void func_001BAAF8(u8 *arg0, u8 *arg1) {
    u8 *s1 = arg0;
    u8 *s5 = *(u8 **)(arg1 + 0x38);
    s32 s3 = 0;
    f32 f20;
    f32 f1;
    f32 f2;
    f32 t;
    s32 r;
    s32 s0;
    s32 s2;
    s32 v0;

    if (*(f32 *)(s1 + 0x138) <= 0.0f) {
        f20 = D_00385100;
        do {
            s0 = 0x2BC - *(s32 *)(gEftPtcl3Mgr + 8);
            s2 = 0;
            if (s0 > 0) {
                /* cvt.w.s (truncates toward zero) of 0x8C(s1) */
                t = *(f32 *)(s1 + 0x8C);
                r = (s32)t;
                s3 = r;
                v0 = s0 < s3;
                if (0.0f < *(f32 *)(s1 + 0x90)) {
                    f1 = (f32)rand() / f20;
                    f2 = (f32)s3 + *(f32 *)(s1 + 0x90) * f1;
                    /* cvt.w.s (truncates toward zero) of f2 */
                    t = f2;
                    r = (s32)t;
                    s3 = r;
                    v0 = s0 < s3;
                }
                s2 = 1;
                if (v0 != 0) {
                    s3 = s0;
                }
            }
            if (s2 != 0) {
                func_001B9470((s32)s1, (s32)arg1, s3);
            }
            f1 = *(f32 *)(s1 + 0x138) + *(f32 *)(s5 + 0x5C);
            *(f32 *)(s1 + 0x138) = f1;
        } while (s2 != 0 && f1 <= 0.0f);
    }
}
