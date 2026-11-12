#include "common.h"

extern f32 D_003858F0;

void *func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(s32 arg0);
s32 func_0023F410(s32 arg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
void *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00240040(s32 arg0);
s32 BtlKiBlast_GetHitsOf_240980(s32 arg0);
s32 func_002403E0(s32 arg0);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_00241718(s32 arg0, s32 arg1);
s32 func_00240FF0(s32 arg0, s32 arg1);
void func_00210000(s32 arg0, s32 arg1);
void func_00203810(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);

s32 func_00202798(s32 arg0, u8 *arg1) {
    s32 sp[4];
    f32 f20;
    f32 t;
    u8 *s2;
    u8 *v1p;
    u8 *s1p;
    s32 s0;
    s32 s4;
    s32 ret;
    s32 hits;
    s32 tv0;
    s32 doit;
    s32 go7;

    s4 = 0;
    s2 = func_00211288(arg0);
    ret = 0;
    if (*(s32 *)(arg1 + 0x54) != 1) {
        go7 = 0;
        if (func_00211310((s32)s2, 3, 0x30) != 0) {
            go7 = 1;
        } else {
            s0 = 0;
            if (func_00211310((s32)s2, 3, 0x4000) != 0 && *(s32 *)(s2 + 0x1170) > 0 &&
                (func_0023F410((s32)s2) & 2)) {
                s0 = 1;
                func_002113C0((s32)s2, 4, 0x80000, 1);
            }
            ret = 0;
            go7 = (s0 != 0);
        }
        if (go7) {
            ret = func_00212820((s32)s2);
            if (ret != 0) {
                f20 = func_00200550((s32)s2, (s32)arg1, (s32)sp);
                ret = 0;
                t = BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos((s32)s2) + 0x14) - f20);
                if (t < 0.0f) {
                    t = -t;
                }
                if (!(t < D_003858F0)) {
                    if (*(s32 *)(arg1 + 0xC) != 0) {
                        v1p = *(u8 **)(arg1 + 0x64);
                        ret = 0;
                        if (v1p != NULL) {
                            s0 = *(s32 *)(v1p + 4);
                            s1p = func_00211288(*(s32 *)v1p);
                            doit = 0;
                            if (s0 < 0) {
                                doit = 1;
                            } else if (s0 < 2) {
                                doit = 0;
                            } else if (s0 >= 5) {
                                doit = 1;
                            } else if (func_002411E0((s32)s1p, s0) & 2) {
                                s4 = func_00241718((s32)s1p, s0);
                                tv0 = func_00240FF0((s32)s1p, s0);
                                if (tv0 >= 2) {
                                    s4 = s4 / tv0;
                                }
                                doit = 1;
                            }
                            if (doit) {
                                func_00210000((s32)(arg1 + 0x20), 0x37);
                                func_00203810((s32)s2, s4);
                                func_00206958((s32)s2, (s64)0x8000 << 26);
                                ret = 1;
                                *(s32 *)(s2 + 0x1478) = *(s32 *)(s2 + 0x1478) + 1;
                            }
                        }
                    } else {
                        ret = 0;
                        doit = 0;
                        if (!(func_00240040((s32)arg1) & 2)) {
                            hits = BtlKiBlast_GetHitsOf_240980((s32)arg1);
                            if (hits >= 0x10 || hits < 0xE) {
                                s4 = func_002403E0((s32)arg1) * 3;
                                doit = 1;
                            }
                        }
                        if (doit) {
                            func_00210000((s32)(arg1 + 0x20), 0x37);
                            func_00203810((s32)s2, s4);
                            func_00206958((s32)s2, (s64)0x8000 << 26);
                            ret = 1;
                            *(s32 *)(s2 + 0x1478) = *(s32 *)(s2 + 0x1478) + 1;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
