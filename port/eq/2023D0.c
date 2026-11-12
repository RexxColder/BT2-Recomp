#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define H(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))

s32 func_00211288(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
s32 BtlKiBlast_GetHitsOf_240980(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
s32 func_00203968(s32 arg0, s32 arg1);
void func_00210000(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211418(s32 arg0, s32 arg1);
s32 func_00212820(s32 arg0);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_00218128(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 func_00240040(s32 arg0);

extern f32 D_003858E8;

s32 func_002023D0(s32 arg0, s32 arg1) {
    s32 sp[4];
    s32 s0;
    s32 s2;
    s32 pos;
    s32 t;
    s32 v;
    f32 f20;
    f32 w;
    f32 aw;

    s2 = 0;
    s0 = func_00211288(arg0);
    if (W(arg1, 0xC) != 0) {
        return 0;
    }
    if (W(arg1, 0x54) == 1) {
        return 0;
    }
    if (W(arg1, 0x68) == 0) {
        return 0;
    }
    if (func_00240040(arg1) & 2) {
        return 0;
    }
    if (func_00212820(s0) == 0) {
        return 0;
    }
    if (func_00211310(s0, 3, 0x30) == 0) {
        if (func_00218128(s0, 7) != 0) {
            func_00210000(arg1 + 0x20, 0x13);
            return 1;
        }
    }

    f20 = func_00200550(s0, arg1, (s32)sp);
    pos = BtlChar_GetPos(s0);
    w = BtlUtil_WrapAngle(F(pos, 0x14) - f20);
    aw = (w < 0.0f) ? -w : w;
    if (aw < D_003858E8) {
        return 0;
    }

    if (func_00211310(s0, 3, 0x4000) != 0) {
        if (W(s0, 0x1170) > 0) {
            if (!(func_0023F410(s0) & 2)) {
                s2 = 1;
                func_002113C0(s0, 4, 0x80000, 1);
            }
        }
    }

    if (s2 == 0) {
        t = H(W(arg1, 0x68), 0x18);
        if (t != 4) {
            if (t >= 5) {
                if (t == 8) {
                    goto block_22;
                }
                goto block_24;
            }
            if (t != 0) {
                goto block_24;
            }
        }
block_22:
        v = func_00211310(s0, 3, 0x40);
        if (v == 0) {
            return v;
        }
        goto block_25;
block_24:
        v = func_00211310(s0, 3, 0x80);
        if (v == 0) {
            return v;
        }
    }

block_25:
    v = BtlKiBlast_GetHitsOf_240980(arg1);
    if (v >= 0x10) {
        func_00210000(arg1 + 0x20, 0x13);
    } else if (v < 0xE) {
        func_00210000(arg1 + 0x20, 0x13);
    } else {
        func_00210000(arg1 + 0x20, (BtlChar_FrameMod(2) == 0) ? 0xD : 0xC);
    }
    func_00212DD8(s0, 0xB);
    func_00203968(s0, 0x2710);
    func_002113C0(s0, 0x10, 0x02000000, 1);
    W(s0, 0x1478) = W(s0, 0x1478) + 1;
    func_00211418(s0, 0x02000000);
    return 1;
}
