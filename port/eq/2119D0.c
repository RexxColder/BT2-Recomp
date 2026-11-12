#include "common.h"

extern f32 D_00385A38;
extern f32 D_00385A3C;

void BtlChar_Vibrate(void *a0, f32 f12, f32 f13);
void BtlMember_AddHealth(void *a0, s32 a1);
s32 BtlMember_DrainKi(void *a0, s32 a1);
s32 BtlObjXf_Update(void *a0);
s32 func_001FA3A8(s32 a0);
f32 func_001FA308(void *a0);
s32 func_00203310(void *a0, s32 a1, s32 a2);
void func_00203810(void *a0, s32 a1);
f32 func_0020A2F8(s32 a0);
s32 func_0020A658(s32 a0);
s32 func_0020A758(s32 a0);
s32 func_00210DD8(void *a0);
s32 func_00211270(void);
void *func_00211288(s32 a0);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_00217488(void *a0);
s32 func_002411E0(void *a0, s32 a1);
s32 func_0025FBE8(void *a0, s64 a1);

void func_002119D0(void) {
    f32 f20 = 1.0f;
    f32 f21 = D_00385A3C;
    f32 f22 = D_00385A38;
    s32 s4 = 0;
    u8 *s0;
    u8 *s2;
    s32 s1;
    s32 s3;
    s32 a1;
    s32 v;
    s32 amt;
    s32 r;
    s32 flag;
    f32 ff;

    while (s4 < func_00211270()) {
        if (func_0020A658(s4) != 0) {
            s4 += 1;
            continue;
        }
        s0 = (u8 *)func_00211288(s4);
        s2 = (u8 *)func_00211288(func_00210DD8(s0));

        if (func_0025FBE8((void *)*(s32 *)(s0 + 0x1530), (s64)0x8000 << 18) != 0) {
            s1 = -1;
            switch (func_00217488(s0)) {
            case 0xC2:
                s1 = 3;
                break;
            case 0xCD:
                s1 = 2;
                break;
            case 0xC1:
                s1 = 2;
                break;
            case 0xCE:
                s1 = 3;
                break;
            case 0xC3:
            case 0xCF:
                s1 = 4;
                break;
            }

            a1 = *(s32 *)(s0 + 0x9C8);
            if (a1 > 0) {
                v = *(s32 *)(s0 + 0x9D0);
                if (v > 0) {
                    if (v < 2) {
                        func_00203310(s2, a1, *(s32 *)(s0 + 0x9D4));
                        *(s32 *)(s0 + 0x9C8) = 0;
                        BtlChar_Vibrate(s0, f20, f21);
                        BtlChar_Vibrate(s2, f20, f21);
                    } else {
                        func_00203310(s2, *(s32 *)(s0 + 0x9CC), *(s32 *)(s0 + 0x9D4));
                        *(s32 *)(s0 + 0x9C8) = *(s32 *)(s0 + 0x9C8) - *(s32 *)(s0 + 0x9CC);
                        BtlChar_Vibrate(s0, f20, f22);
                        BtlChar_Vibrate(s2, f20, f22);
                    }
                    v = *(s32 *)(s0 + 0x9D0) - 1;
                    *(s32 *)(s0 + 0x9D0) = v;
                    flag = 1;
                    if (s1 >= 0) {
                        flag = ((func_002411E0(s0, s1) & 0x20000000) == 0);
                    }
                    if (flag != 0) {
                        *(s32 *)(s2 + 0xB78) = 10;
                    }
                }
            }
        }

        /* tail: runs on both paths */
        s3 = 0;
        r = func_001FA3A8(BtlObjXf_Update(s0));
        s1 = 0;
        if (r & 8) {
            if (!(func_001FA3A8(BtlObjXf_Update(s0)) & 0x10)) {
                s3 = 1;
                ff = func_001FA308(s0);
                r = (s32)ff;
                if ((ff - (f32)r > 0.5f) || ((ff - (f32)r == 0.5f) && (r & 1))) {
                    r += 1;
                } else if ((ff - (f32)r < -0.5f) || ((ff - (f32)r == -0.5f) && (r & 1))) {
                    r -= 1;
                }
                s1 = r;
            }
        }
        if (func_0020A758(*(s32 *)(s0 + 0x1534)) != 0) {
            s3 = 1;
            ff = func_0020A2F8(*(s32 *)(s0 + 0x1534));
            r = (s32)ff;
            if ((ff - (f32)r > 0.5f) || ((ff - (f32)r == 0.5f) && (r & 1))) {
                r += 1;
            } else if ((ff - (f32)r < -0.5f) || ((ff - (f32)r == -0.5f) && (r & 1))) {
                r -= 1;
            }
            s1 = r;
        }

        if (s3 != 0) {
            if (*(s32 *)(s0 + 0x9F0) < s1) {
                v = *(s32 *)(s0 + 0x9DC);
                if (v > 0) {
                    a1 = *(s32 *)(s0 + 0x9E0);
                    if (a1 < v) {
                        *(s32 *)(s0 + 0x9DC) = v - a1;
                        amt = a1;
                    } else {
                        *(s32 *)(s0 + 0x9DC) = 0;
                        amt = v;
                    }
                    r = func_00203310(s2, amt, *(s32 *)(s0 + 0x9D4) | 0xB);
                    BtlMember_AddHealth(s0, r);
                    *(s32 *)(s2 + 0xB78) = 10;
                }
                v = *(s32 *)(s0 + 0x9E8);
                if (v > 0) {
                    a1 = *(s32 *)(s0 + 0x9EC);
                    if (a1 < v) {
                        *(s32 *)(s0 + 0x9E8) = v - a1;
                        amt = a1;
                    } else {
                        *(s32 *)(s0 + 0x9E8) = 0;
                        amt = v;
                    }
                    r = BtlMember_DrainKi(s2, amt);
                    func_00203810(s0, r);
                    *(s32 *)(s2 + 0xB78) = 10;
                }
            }
        }

        if (func_00211310(s0, 5, 0x100) == 0) {
            s4 += 1;
            continue;
        }

        a1 = *(s32 *)(s0 + 0x9C8);
        if (a1 > 0) {
            func_00203310(s2, a1, *(s32 *)(s0 + 0x9D4));
        }
        *(s32 *)(s0 + 0x9F0) = 0;

        *(s32 *)(s0 + 0x9C4) = 0;
        *(s32 *)(s0 + 0x9C8) = 0;
        *(s32 *)(s0 + 0x9D0) = 0;
        *(s32 *)(s0 + 0x9CC) = 0;
        *(s32 *)(s0 + 0x9D4) = 0;
        *(s32 *)(s0 + 0x9D8) = 0;
        *(s32 *)(s0 + 0x9DC) = 0;
        *(s32 *)(s0 + 0x9E0) = 0;
        *(s32 *)(s0 + 0x9E4) = 0;
        *(s32 *)(s0 + 0x9E8) = 0;
        *(s32 *)(s0 + 0x9EC) = 0;
        s4 += 1;
    }
}
