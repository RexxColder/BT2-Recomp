#include "common.h"

extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00211288(s32 arg0);
extern s32 func_001FD1F0(void *arg0);
extern s32 func_002417E8(s32 arg0, s32 arg1);
extern s32 func_0023F440(s32 arg0, s32 arg1);
extern s32 func_002411E0(s32 arg0, s32 arg1);
extern s32 func_00241958(s32 arg0, s32 arg1);
extern s32 func_00240FC8(s32 arg0, s32 arg1);
extern f32 func_002415A0(s32 arg0, s32 arg1);
extern s32 func_00241920(s32 arg0, s32 arg1);
extern s32 func_00212408(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00210000(s32 arg0, s32 arg1);
extern f32 func_00200550(u8 *arg0, u8 *arg1, f32 *arg2);
extern s32 func_00203C58(s32 a0, s64 a1);
extern void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00203310(u8 *arg0, s32 arg1, s32 arg2, f32 arg3);
extern void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg0, f32 *arg1);
extern void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
extern void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern s32 BtlChar_GetPos(s32 arg0);
extern f32 BtlUtil_WrapAngle(f32 farg0);
extern s32 BtlChar_FrameMod(s32 arg0);
extern f32 D_003858AC;
extern f32 D_003858B0;
extern f32 D_003858B4;

s32 func_00200AD0(u8 *chr, u8 *task) {
    f32 euler[4];
    s32 *link;
    s32 self;
    s32 sub;
    s32 kind;
    s32 type;
    s32 hurtKind;
    s32 amount;
    s32 skip = 0;
    f32 baseAng;
    f32 delta;
    f32 gain;

    if (func_00211310((s32)chr, 3, 4) != 0) {
        return 0;
    }
    link = *(s32 **)(task + 0x64);
    if (link == 0) {
        return 0;
    }
    sub = link[1];
    self = func_00211288(link[0]);
    kind = func_001FD1F0(chr);
    type = func_002417E8(self, sub);
    if (type < 0x1D) {
        if (type >= 0x1B) {
            if (func_0023F440((s32)chr, (s32)task) == 4 && !(func_002411E0(self, sub) & 0x100000)) {
                hurtKind = func_00241958(self, sub);
                if (hurtKind == 1) {
                    func_00210000((s32)(task + 0x20), BtlChar_FrameMod(2) != 0 ? 0x1B : 0x11);
                    return 1;
                }
                if (hurtKind < 2) {
                    return 1;
                }
                if (hurtKind == 2) {
                    func_00210000((s32)(task + 0x20), 0x47);
                    return 1;
                }
                if (hurtKind == 3) {
                    func_00210000((s32)(task + 0x20), 0x4A);
                    return 1;
                }
                return 1;
            }
            skip = 1;
        }
    }
    baseAng = func_00200550(chr, task, euler);
    if (kind != 9) {
        delta = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos((s32)chr) + 0x14) - baseAng);
        if (__builtin_fabsf(delta) < D_003858AC) {
            return 0;
        }
    }
    if (func_002411E0(self, sub) & 1) {
        if (skip) {
            return 0;
        }
        if (kind != 9) {
            return 0;
        }
    }
    if (func_00203C58(self, 0x10000000) != 0 && kind != 9) {
        return 0;
    }
    if ((func_00240FC8(self, sub) & 3) != 0 && D_003858B0 <= *(f32 *)((u8 *)self + 0xA30)
        && (func_002411E0(self, sub) & 8) != 0 && kind != 9) {
        return 0;
    }
    if (kind == 0) {
        return 0;
    }
    if (kind == 7) {
        return 0;
    }
    gain = func_002415A0(self, sub);
    switch (func_00241920(self, sub)) {
    case 0:
        func_002113C0(chr, 4, 0x200, 1);
        break;
    case 1:
    case 2:
        func_002113C0(chr, 4, 0x400, 1);
        break;
    default:
        break;
    }
    amount = func_00212408(self, sub, 1, 0);
    if (kind == 8) {
        amount = amount / 2;
    }
    func_00203310(chr, amount, func_00203C58(self, 0x8000000) != 0 ? 13 : 12, 0.0f);
    hurtKind = func_00241958(self, sub);
    if (hurtKind == 1) {
        func_00210000((s32)(task + 0x20), BtlChar_FrameMod(2) != 0 ? 0x1B : 0x11);
    } else if (hurtKind == 2) {
        func_00210000((s32)(task + 0x20), 0x47);
    } else if (hurtKind == 3) {
        func_00210000((s32)(task + 0x20), 0x4A);
    }
    Vec3_DiffToEuler_20E478(gain, (s32)chr, euler);
    func_001FBE80((s32)chr, 5.0f, D_003858B4);
    BtlChar_Vibrate((s32)chr, 1.0f, D_003858B4);
    return 1;
}
