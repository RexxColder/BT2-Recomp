#include "common.h"

u8 *func_001272E0(s32 arg0, f32 farg0, f32 farg1);
u8 *BtlChar_GetPos(s32 arg0);
void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
f32 sceVu0InnerProduct(u8 *arg0, u8 *arg1);
f32 func_0029DFD0(u8 *arg0);
extern f32 D_00385B34;
extern f32 D_00385B38;

s32 func_00218580(s32 arg0, f32 farg0, f32 farg1) {
    u8 sp[0x20];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *pos;
    u8 *ptr;
    s32 s3;
    s32 s4;
    s32 v0;
    s32 v1;
    s32 cond;
    f32 dot;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 ratio;

    s3 = 0;
    s4 = 0;
    s1 = func_001272E0(arg0, farg0, farg1);
    f21 = D_00385B34;
    if (*(s32 *)(s1 + 0x6000) <= 0) {
        return 0;
    }
    s2 = s1;
    do {
        if (*(s32 *)(s2 + 0x54) != 1) {
            s0 = s2 + 0x20;
            func_00312650(sp, s0, s2 + 0x30);
            pos = BtlChar_GetPos(arg0);
            func_00312650(sp + 0x10, pos, s0);
            dot = sceVu0InnerProduct(sp + 0x10, sp);
            if (!(dot < 0.0f)) {
                f20 = func_0029DFD0(sp + 0x10);
                f1 = func_0029DFD0(sp);
                if (!(f1 < D_00385B38)) {
                    ratio = f20 / f1;
                    v0 = *(s32 *)(s2 + 0xC);
                    if (v0 == 0) {
                        cond = (farg0 < ratio);
                    } else {
                        cond = (farg1 < ratio);
                    }
                    if (!cond && (f20 < f21)) {
                        f21 = f20;
                        if (v0 != 0) {
                            s3 = 3;
                        } else {
                            ptr = *(u8 **)(s2 + 0x68);
                            if (ptr == NULL) {
                                s3 = 1;
                            } else {
                                v1 = *(s16 *)(ptr + 0x18);
                                if (v1 == 4) {
                                    s3 = 1;
                                } else if (v1 < 5) {
                                    s3 = (v1 == 0) ? 1 : 2;
                                } else {
                                    s3 = (v1 == 8) ? 1 : 2;
                                }
                            }
                        }
                    }
                }
            }
        }
        s4 += 1;
        s2 += 0x180;
    } while (s4 < *(s32 *)(s1 + 0x6000));
    return s3;
}
