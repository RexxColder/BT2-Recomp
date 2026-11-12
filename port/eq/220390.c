#include "common.h"

extern f32 D_00385F10;
extern f32 D_00385F14;
extern f32 D_00385F18;
extern f32 D_00385F1C;

s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 func_00217488(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_001FA360(s32 arg0, f32 farg0);
f32 func_001FA318(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00218838(s32 arg0, s32 arg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

/* 0x00220390: per-frame update of the actor at arg0. Unless the actor is health-empty,
 * a pad/state check picks a 4.0 or a computed (2 * blend) impulse through func_001FA360,
 * then the common tail runs the mode setters and the 0x211310 / 0x2113C0 flag pairs. */
s32 func_00220390(u8 *self)
{
    f32 f20;
    s32 r;

    if (!BtlMember_IsHealthEmpty_2127F8((s32)self)) {
        if (func_00217488((s32)self) == 0x9C) {
            if (BtlPad_Test4C((s32)self, 0x18)) {
                func_001FA360((s32)self, 4.0f);
            } else {
                f32 probe = func_001FA318((s32)self);
                if (D_00385F10 < probe) {
                    f32 half = ((1.0f - *(f32 *)(self + 0xB58)) * 0.5f) + 0.5f;
                    func_001FA360((s32)self, half + half);
                }
            }
        } else {
            if (BtlPad_Test4C((s32)self, 0x18)) {
                func_001FA360((s32)self, 4.0f);
            }
        }
    }

    f20 = D_00385F14;
    func_001F9FB0((s32)self, 0);
    func_00215068((s32)self, 5, 12, D_00385F18, f20);

    if (func_00218838((s32)self, 0)) {
        func_00215E88(f20, (s32)self, 2);
    } else {
        func_00215E88(f20, (s32)self, 4);
    }

    func_00216208((s32)self, 0.0f, D_00385F1C);
    func_00216678((s32)self);
    func_002113C0((s32)self, 9, 0x200, 1);
    func_002113C0((s32)self, 6, 4, 1);
    func_002113C0((s32)self, 6, 8, 1);
    func_002113C0((s32)self, 3, 0x2000, 1);
    func_002113C0((s32)self, 3, 0x4000, 1);
    func_002113C0((s32)self, 1, 0x400000, 1);
    func_002113C0((s32)self, 15, 1, 1);

    if (func_00211310((s32)self, 0, 0x100)) {
        func_002113C0((s32)self, 0, 2, 1);
    }

    r = func_00211310((s32)self, 0, 4);
    if (r) {
        return func_002113C0((s32)self, 0, 2, 0);
    }
    return r;
}
