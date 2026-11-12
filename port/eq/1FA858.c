#include "common.h"

extern f32 Mathf_Asin(f32 arg0);
extern f32 atan2f(f32 arg0, f32 arg1);
extern f32 cosf(f32 arg0);
extern f32 sinf(f32 arg0);
extern void func_001FCD80(void *arg0);
extern void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
extern s32 func_00210DD8(void *arg0);
extern void *func_00211288(s32 arg0);
extern void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 func_0029DFD0(void *arg0);
extern void func_00312638(void *arg0, void *arg1, void *arg2);
extern void func_00312650(void *arg0, void *arg1, void *arg2);
extern void func_00312680(void *arg0, void *arg1, f32 f12);
extern void func_003126C8(void *arg0, void *arg1);
extern u8 D_002C3630[] __attribute__((section(".data")));
extern f32 D_003857E0;

void func_001FA858(void *arg0, void *arg1, void *arg2, void *arg3) {
    f32 sp0[4];
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    u8 *s1;
    u8 *s0;
    u8 *s2;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    u8 *s7;
    f32 *out;
    s32 sp48;
    s32 sp4C;
    f32 f21;
    f32 f20;
    f32 f22;
    f32 f23;
    f32 f12;
    f32 fa;
    f32 fb;
    f32 tmp;
    s32 v0;
    s32 v1;

    s1 = (u8 *)arg0 + 0x150;
    out = (f32 *)arg2;
    f21 = 0.0f;
    sp48 = 0;
    sp4C = 0;
    v0 = *(s32 *)(s1 + 0x14C);
    if (v0 > 0) {
        f21 = 1.0f - ((f32)*(s32 *)(s1 + 0x148) / (f32)v0);
    }

    v1 = *(s32 *)(s1 + 0x138);
    if (v1 >= 0) {
        if (!(v1 & 0x40000000)) {
            v0 = *(s32 *)((u8 *)arg0 + 0x1534);
        } else {
            v0 = func_00210DD8(arg0);
            sp4C = 1;
        }
        s7 = s1 + 0xC0;
        func_00208DE8(v0, s7, v1 & 0xBFFFFFFF);
        sp48 = 1;
    } else {
        s7 = (u8 *)arg0 + 0x210;
    }

    v1 = *(s32 *)(s1 + 0x13C);
    s5 = s1 + 0xD0;
    if (v1 >= 0) {
        if (*(s32 *)(s1 + 0x138) != v1) {
            if (v1 & 0x40000000) {
                sp4C = 1;
                v0 = func_00210DD8(arg0);
            } else {
                v0 = *(s32 *)((u8 *)arg0 + 0x1534);
            }
            func_00208DE8(v0, sp20, v1 & 0xBFFFFFFF);
            func_00312650(s5, sp20, s7);
        } else {
            func_003126C8(s5, D_002C3630);
        }
        sp48 = 1;
    }

    v1 = *(s32 *)(s1 + 0x140);
    if (v1 >= 0) {
        if (!(v1 & 0x40000000)) {
            v0 = *(s32 *)((u8 *)arg0 + 0x1534);
        } else {
            v0 = func_00210DD8(arg0);
        }
        s6 = s1 + 0x100;
        func_00208DE8(v0, s6, v1 & 0xBFFFFFFF);
    } else {
        s6 = s1 + 0x100;
    }

    v1 = *(s32 *)(s1 + 0x144);
    s4 = s1 + 0x110;
    if (v1 >= 0) {
        if (*(s32 *)(s1 + 0x140) != v1) {
            if (!(v1 & 0x40000000)) {
                v0 = *(s32 *)((u8 *)arg0 + 0x1534);
            } else {
                v0 = func_00210DD8(arg0);
            }
            func_00208DE8(v0, sp30, v1 & 0xBFFFFFFF);
            func_00312650(s4, sp30, s6);
        } else {
            func_003126C8(s5, D_002C3630);
        }
    }

    s2 = s1 + 0xE0;
    s0 = s1 + 0xF0;
    if (sp48 != 0) {
        if (sp4C == 0) {
            func_003126C8(s2, *(void **)(*(u8 **)((u8 *)arg0 + 0x1530) + 0xF40));
        } else {
            u8 *t;
            t = (u8 *)func_00211288(func_00210DD8(arg0));
            func_003126C8(s2, *(void **)(*(u8 **)(t + 0x1530) + 0xF40));
        }
        s0 = s1 + 0xF0;
        func_003126C8(s0, D_002C3630);
    }

    func_00312680(arg1, s5, f21);
    func_00312638(arg1, arg1, s7);
    func_00312680(arg3, s0, f21);
    func_00312638(arg3, arg3, s2);
    func_00312680(sp0, s4, f21);
    func_00312638(sp0, sp0, s6);

    f22 = *(f32 *)(s1 + 0x120) + (*(f32 *)(s1 + 0x124) * f21);
    f20 = -(*(f32 *)(s1 + 0x128) + (*(f32 *)(s1 + 0x12C) * f21));
    f23 = *(f32 *)(s1 + 0x130) + (*(f32 *)(s1 + 0x134) * f21);
    fa = cosf(f20);
    sp10[0] = fa * sinf(f22);
    sp10[1] = sinf(f20);
    fb = cosf(f20);
    sp10[2] = fb * cosf(f22);
    func_00312680(sp10, sp10, f23);
    func_00312650(arg1, arg1, sp10);
    out[0] = 0.0f;
    out[3] = 0.0f;
    out[2] = 0.0f;
    out[1] = 0.0f;
    func_00312650(sp10, sp0, arg1);

    tmp = func_0029DFD0(sp10);
    if (D_003857E0 < tmp) {
        func_00312680(sp10, sp10, 1.0f / tmp);
        f21 = sp10[0];
        if (f21 > 1.0f) {
            sp10[0] = 1.0f;
            f21 = 1.0f;
        }
        if (f21 < -1.0f) {
            sp10[0] = -1.0f;
        }
        f12 = sp10[1];
        if (f12 > 1.0f) {
            f12 = 1.0f;
            sp10[1] = 1.0f;
        }
        f20 = sp10[2];
        if (f12 < -1.0f) {
            f12 = -1.0f;
            sp10[1] = -1.0f;
            f20 = sp10[2];
        }
        if (f20 > 1.0f) {
            f20 = 1.0f;
            sp10[2] = 1.0f;
        }
        if (f20 < -1.0f) {
            sp10[2] = -1.0f;
        }
        out[0] = Mathf_Asin(-f12);
        out[1] = atan2f(sp10[0], sp10[2]);
    }

    v1 = *(s32 *)(s1 + 0x150);
    if (v1 & 2) {
        func_002113C0(arg0, 0xE, 0x40, 1);
    }
    v1 = *(s32 *)(s1 + 0x150);
    if (v1 & 0x10) {
        func_002113C0(arg0, 0xE, 0x400, 1);
    }
    v1 = *(s32 *)(s1 + 0x150);
    if (v1 & 0x40) {
        func_002113C0(arg0, 0xE, 0x800, 1);
    }

    v0 = *(s32 *)(s1 + 0x148);
    if (v0 > 0) {
        v0 = v0 - 1;
        *(s32 *)(s1 + 0x148) = v0;
        if (v0 == 0) {
            v1 = *(s32 *)(s1 + 0x150);
            if (!(v1 & 0x80)) {
                if (v1 & 4) {
                    func_002113C0(arg0, 0xE, 0x80, 1);
                }
                func_001FCD80(arg0);
            }
        }
    }
    func_002113C0(arg0, 0xE, 0x2000, 1);
}
