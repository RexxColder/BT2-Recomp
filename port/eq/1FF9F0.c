#include "common.h"

#define PF32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PS32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PU8(p, o) (*(u8 *)((u8 *)(p) + (o)))

extern f32 D_00385888;
extern f32 D_0038588C;
extern f32 D_00385890;
extern f32 D_00385894;
extern u8 *D_00387930;

extern u8 *func_00211288(s32 arg0);
extern s32 func_0023E520(u8 *arg0);
extern u8 *BtlChar_GetPos(u8 *arg0);
extern void func_003126C8(u8 *arg0, u8 *arg1);
extern void func_00312650(u8 *arg0, u8 *arg1, u8 *arg2);
extern f32 atan2f(f32 y, f32 x);
extern void Quat_ToEuler(u8 *arg0, u8 *arg1);
extern f32 BtlUtil_WrapAngle(f32 x);
extern u8 *BtlObjXf_Update(u8 *arg0);
extern s32 func_001FA3A8(u8 *arg0);
extern s32 func_0023EEB8(u8 *a);
extern s32 func_0023EEF0(u8 *a);
extern s32 func_0023EE80(u8 *a);
extern s32 func_00217488(u8 *a);
extern s32 func_0023EF80(u8 *a);
extern s32 func_0023F410(u8 *a);
extern s32 func_00218128(u8 *a, s32 b);
extern s32 BattleResult_GetFlags(u8 *a);
extern s32 func_0023EE48(u8 *a);
extern s32 func_0023EE28(u8 *a);
extern s32 func_0023EF48(u8 *a);
extern s32 BtlObjAnim_QueryEvent(u8 *a, s32 b, s32 c, s32 d);
extern void func_002113C0(u8 *a, s32 b, s32 c, s32 d);
extern s32 func_0023EF28(u8 *a);
extern f32 func_0023F278(u8 *a);
extern f32 func_0023FC68(u8 *a);
extern s32 func_00212878();
extern f32 BtlMember_GetHealthRatio(u8 *a);
extern f32 func_0023F140(u8 *a);
extern s32 func_001FD1A8(s32 a);
extern void func_00212DD8(u8 *a, s32 b);
extern void func_00203888(u8 *a, s32 b, s32 c);
extern s32 func_0023F298(u8 *a);
extern void func_00206958(u8 *a, s64 b);
extern f32 func_0023F1F8(u8 *a);
extern f32 func_0023F218(u8 *a);
extern void func_001FBE80(u8 *a, f32 b, f32 c);
extern void BtlChar_Vibrate(u8 *a, f32 b, f32 c);
extern f32 func_0023F178(u8 *a);
extern f32 func_0023F1B8(u8 *a);
extern u8 *BtlMember_GetActiveGauge(u8 *a);
extern f32 func_0023EFD8(u8 *a);
extern void func_0020E4B0(u8 *a, f32 b, f32 c);
extern s32 func_0023EAE0(u8 *a);
extern void func_00203310(u8 *a, s32 b, s32 c);
extern s32 func_00211310(u8 *a, s32 b, s32 c);
extern s32 func_0023ED10(u8 *a);
extern s32 func_00203C58(u8 *a, s64 b);
extern void func_00203810(u8 *a, s32 b);
extern s32 func_0023EDC8(u8 *a);
extern void func_001FCE88(u8 *a, s32 b);
extern void func_001FD088(u8 *a, s32 b);
extern void func_001FD138(s32 a);

void func_001FF9F0(u8 *self) {
    u8 sp[0x50];
    s32 flag40 = 0;
    s32 fp = 0;
    f32 f23 = 0.0f;
    f32 f20, f21, f22;
    u8 *other;
    s32 kind, xf, mode, s6, s0, s4, v;
    s32 sidx = PS32(self, 0xBF0);

    if (sidx < 0) {
        return;
    }
    other = func_00211288(sidx);
    kind = func_0023E520(self);
    func_003126C8(sp, BtlChar_GetPos(self));
    func_003126C8(sp + 0x10, BtlChar_GetPos(other));
    func_00312650(sp + 0x20, sp + 0x10, sp);
    if (D_00385888 < __builtin_fabsf(*(f32 *)(sp + 0x20)) || D_00385888 < __builtin_fabsf(*(f32 *)(sp + 0x28))) {
        f23 = atan2f(*(f32 *)(sp + 0x20), *(f32 *)(sp + 0x28));
    }
    Quat_ToEuler(sp + 0x30, BtlChar_GetPos(other) + 0x80);
    {
        f32 a = PF32(BtlChar_GetPos(other), 0x14) + *(f32 *)(sp + 0x34);
        f32 w = BtlUtil_WrapAngle(a);
        f32 w2 = BtlUtil_WrapAngle(w - f23);
        if (__builtin_fabsf(w2) < D_0038588C) {
            fp = 1;
        }
    }
    xf = func_001FA3A8(BtlObjXf_Update(other));
    mode = xf;
    if (xf & 0x200000) {
        s0 = func_0023EEB8(self);
    } else if (xf & 0x400000) {
        s0 = func_0023EEF0(self);
        PS32(self, 0x1444) = PS32(self, 0x1444) + 1;
    } else if (xf & 0x800000) {
        s0 = func_0023EE80(self);
    } else if (func_00217488(other) == 0x9C || (xf & 0x40000) != 0) {
        s0 = func_0023EF80(self);
    } else {
        s32 c;
        s32 r;
        s0 = 1;
        r = func_0023F410(other);
        c = (r & 4) != 0;
        r = func_0023F410(other);
        if (r & 8) c = c - 1;
        r = func_0023F410(self);
        if (r & 4) c = c - 1;
        r = func_0023F410(self);
        if (r & 8) c = c + 1;
        if (func_00218128(other, 6)) c = 1;
        if (0 < PS32(other, 0xAD8)) c = 1;
        if (c > 0) {
            if (BattleResult_GetFlags(self) & 4) {
                s0 = 2;
                if (func_0023F410(other) & 4) {
                    flag40 = 1;
                }
                goto have_s0;
            }
        }
        if (xf & 0x100000) {
            s0 = func_0023EE48(self);
        } else if ((xf & 0x20000) == 0) {
            s0 = func_0023EE28(self);
        } else if (fp) {
            s0 = func_0023EE28(self);
        } else if (BtlObjAnim_QueryEvent(*(u8 **)((u8 *)other + 0x1530), 1, 0, 2)
                   && (s32)*(s8 *)(*(u8 **)((u8 *)other + 0x1530) + 0xD7D)
                          == ~(s32)*(s8 *)(*(u8 **)((u8 *)other + 0x1530) + 0xD7C)) {
            s0 = func_0023EE28(self);
        } else {
            s0 = func_0023EF48(self);
        }
    }
have_s0:
    s6 = s0 < 18;
    if (s0 == 1) {
        func_002113C0(self, 4, 8, 1);
        return;
    }
    if (s6 || (s0 >= 21 && s0 != 35)) {
        if (0 < PS32(other, 0xADC)) {
            s0 = 2;
        }
        s6 = s0 < 18;
    }
    PS32(other, 0xB48) = s0;
    if (s0 == 2) {
        PS32(other, 0xB7C) = 3;
        if (flag40) {
            func_00203888(other, 2000, 0);
        }
    } else {
        f32 t;
        PS32(other, 0xB4C) = func_0023EF28(self);
        f20 = func_0023F278(self);
        t = func_0023FC68(other);
        PF32(other, 0xB58) = PF32(self, 0x9B0) * f20 * t;
        if (func_00212878()) {
            f32 hr = BtlMember_GetHealthRatio(other);
            PF32(other, 0xB58) = PF32(other, 0xB58) * (1.0f - hr);
        }
        PF32(other, 0xB60) = func_0023F140(self);
        if (BattleResult_GetFlags(self) & 0x40) {
            func_002113C0(other, 0, 2, 1);
        }
        func_00212DD8(other, func_001FD1A8(PS32(other, 0xB48)));
    }
    if (func_0023F298(self)) {
        func_00206958(other, 0x800000);
    }
    f22 = func_0023F1F8(self);
    f21 = func_0023F218(self);
    if (BattleResult_GetFlags(self) & 0x800) {
        func_001FBE80(self, f22, f21);
    }
    func_001FBE80(other, f22, f21);
    f21 = f21 * 0.5f;
    f20 = f22 * 0.5f;
    BtlChar_Vibrate(self, f20, f21);
    BtlChar_Vibrate(other, f20, f21);
    func_00206958(self, 0x200000);
    if (BattleResult_GetFlags(self) & 0x10000) func_00206958(self, 0x20000000);
    if (BattleResult_GetFlags(self) & 0x20000) func_00206958(self, 0x40000000);
    if (BattleResult_GetFlags(self) & 0x40000) func_00206958(self, (s32)0x80000000u);
    func_002113C0(self, 5, 8, 0);
    func_002113C0(self, 4, 2, 1);
    if (mode & 2) func_002113C0(self, 4, 0x20, 1);
    if (BattleResult_GetFlags(self) & 0x200) func_002113C0(self, 5, 0x200, 1);

    if (s0 != 2) {
        if (func_001FA3A8(BtlObjXf_Update(self)) & 8) {
            f20 = func_0023F178(self);
            f21 = func_0023F1B8(self);
            PU8(other, 0xB54) = (BattleResult_GetFlags(self) >> 12) & 1;
            if (PU8(BtlMember_GetActiveGauge(self), 0x2C) != 0 && kind == 0x4A) {
                PU8(other, 0xB54) = 0;
                f20 = 0.0f;
                f21 = D_00385890;
            }
            {
                f32 y = PF32(BtlChar_GetPos(self), 0xB4);
                PF32(other, 0xB6C) = f20;
                PF32(other, 0xB5C) = y;
                PF32(other, 0xB70) = f21;
            }
            PS32(other, 0xB64) = 0;
            PS32(other, 0xB68) = 0;
            func_002113C0(self, 3, 0xE, 1);
            func_002113C0(other, 3, 0xE, 1);
        } else {
            f32 g;
            PU8(other, 0xB54) = (u8)fp;
            PF32(other, 0xB5C) = f23;
            g = func_0023EFD8(self);
            func_0020E4B0(other, PF32(other, 0xB5C), g);
            if (BattleResult_GetFlags(self) & 0x100) {
                func_002113C0(other, 6, 1, 1);
                f20 = func_0023F178(self);
                f21 = func_0023F1B8(self);
                if (PU8(other, 0xB54)) {
                    f32 w = BtlUtil_WrapAngle(PF32(other, 0xB5C) + f20);
                    PF32(other, 0xB68) = f21;
                    PF32(other, 0xB64) = w;
                } else {
                    f32 w = BtlUtil_WrapAngle(PF32(other, 0xB5C) + f20);
                    w = BtlUtil_WrapAngle(w + D_00385894);
                    PF32(other, 0xB64) = w;
                    PF32(other, 0xB68) = -f21;
                }
            }
            PS32(other, 0xB6C) = 0;
            PS32(other, 0xB70) = 0;
        }
    }
    if (kind == 0x4A) {
        v = (func_0023F410(self) >> 19) & 1;
        PU8(self, 0xB55) = (u8)v;
        PU8(other, 0xB55) = (u8)v;
    } else {
        PU8(other, 0xB55) = 0;
        PU8(self, 0xB55) = 0;
    }
    if (!s6 && (s0 < 21 || s0 == 35)) {
        PS32(other, 0xB80) = func_0023EAE0(self);
    } else {
        s32 a1 = func_0023EAE0(self);
        s4 = 0;
        if (PU8(other, 0xB54)) {
            if ((func_001FA3A8(BtlObjXf_Update(other)) & 0x100000) == 0) {
                a1 = a1 + (a1 / 2);
            }
        }
        {
            u32 idx = (u32)(kind - 0x33);
            if (idx < 0x2B) {
                if (idx <= 4) s4 = 0x1000;
                else if (idx <= 9) s4 = 0x2000;
                else if (idx == 0x1C || idx == 0x2A) s4 = 0x80;
            }
        }
        func_00203310(other, a1, s4);
    }
    if (!func_00211310(self, 8, 1)) {
        s32 r0, r1;
        r0 = func_0023ED10(self);
        r1 = func_00203C58(self, 0x40);
        if (r1) r0 = r0 + (r0 / 2);
        func_00203810(self, r0);
    }
    v = PS32(self, 0x9B4) + func_0023EDC8(self);
    PS32(self, 0x9B4) = v;
    if (100000 < v) PS32(self, 0x9B4) = 100000;
    if (BattleResult_GetFlags(self) & 0x400) {
        func_002113C0(other, 0, 1, 0);
        if (func_00211310(other, 10, 0x200)) {
            func_002113C0(other, 0, 0x10000, 1);
        }
    }
    s0 = (s0 >= 16) ? (s6 ? 1 : (s0 == 0x26)) : 0;
    {
        s32 cond = s0;
        u32 idx = (u32)(func_0023E520(self) - 0x1B);
        if (idx < 0x4D) {
            s32 bit = 0, pre = 0;
            if (idx == 0 || idx == 24 || idx == 29) { bit = 0x100; pre = 1; }
            else if (idx == 1 || idx == 25 || idx == 30) { bit = 0x200; pre = 1; }
            else if (idx == 2 || idx == 26 || idx == 31) { bit = 0x40; pre = 1; }
            else if (idx == 3 || idx == 27 || idx == 32) { bit = 0x80; pre = 1; }
            else if (idx == 4 || idx == 28 || idx == 33) { bit = 0x400; pre = 1; }
            if (pre) {
                if (cond) func_002113C0(self, 16, bit, 1);
            } else if (idx >= 5 && idx <= 7) {
                func_002113C0(self, 16, 0x4000, 1);
            } else if (idx >= 8 && idx <= 10) {
                func_002113C0(self, 16, 0x8000, 1);
            } else if (idx >= 0x47 && idx <= 0x4B) {
                /* cases 98..102 */
                static const s32 bits[5] = {0x100, 0x200, 0x40, 0x80, 0x400};
                if (cond) func_002113C0(self, 16, bits[idx - 0x47], 1);
                func_002113C0(self, 16, 0x800, 1);
            } else if (idx == 0x4C) {
                func_002113C0(self, 16, 0x1000, 1);
            }
        }
    }
    PS32(self, 0x143C) = PS32(self, 0x143C) + 1;
    if ((PS32(D_00387930, 8) & 4) == 0) {
        PS32(D_00387930, 8) = PS32(D_00387930, 8) | 4;
        func_002113C0(self, 16, 0x4000000, 1);
    }
    if (BattleResult_GetFlags(self) & 1) {
        PS32(other, 0x14A4) = PS32(other, 0x14A4) + 1;
    }
    func_001FCE88(other, kind);
    func_001FD088(self, kind);
    func_001FD138(kind);
}
