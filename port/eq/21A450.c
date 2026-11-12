#include "common.h"

extern f32 D_00385C0C;
extern f32 D_00385C10;
extern f32 D_00385C14;
extern f32 D_00385C18;
extern f32 D_00385C1C;

s32 BtlObjXf_Update(s32 arg0);
void func_002188C8(s32 arg0);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void BtlChar_SetVibration(void *arg0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
void func_001F9D78(void *arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_001FA318(s32 arg0);
s32 func_001FA2E0(s32 arg0);
s32 func_0023F2D8(s32 arg0);
void func_00212DD8(s32 arg0, s32 arg1);
f32 func_001FA308(void *a0);
void func_002182A8(void *a0);
void func_0020FC38(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);

/* 0x0021A450 (battle character state dispatch, same shape as 0x0021F618). The switch on BtlObjXf_Update's result:
 * 0x39 starts a state, 0x50 and 0x51 use func_001FA0A0 with 0x51 and 0x52, 0x52 is the height-timer arm. Every other
 * value, and the end of each arm, goes to the common tail (func_00211310 test, then the fixed calls). f21 starts as
 * D_00385C0C and is zeroed by the 0x39 arm and by a failed test in the tail. */
void func_0021A450(u8 *obj) {
    s32 self = (s32)obj;
    s32 state;
    s32 ev;
    f32 f21 = D_00385C0C;
    f32 f20;

    state = BtlObjXf_Update(self);
    switch (state) {
    case 0x39:
        func_001F9FB0(self, 0);
        f21 = 0.0f;
        func_002113C0(self, 5, 0x800, 1);
        break;

    case 0x50:
        func_002188C8(self);
        func_001FA0A0(self, 0x51, 0);
        break;

    case 0x51:
        func_002188C8(self);
        if (func_001FA0A0(self, 0x52, 0) != 0) {
            BtlChar_SetVibration(obj, 1.0f, D_00385C10);
        } else {
            if (BtlPad_Test48(self, 1) == 0) {
                func_001F9D78(obj, 0x52);
            }
            if (BtlPad_Test4C(self, 3) != 0 || BtlPad_Test4C(self, 2) != 0 || BtlPad_Test4C(self, 0) != 0) {
                func_001F9D78(obj, 0x39);
                func_002182A8(obj);
                func_0020FC38(self, 0x1F);
                *(s32 *)(obj + 0x14A0) += 1;
            }
        }
        *(f32 *)(obj + 0x9B0) = func_001FA318(self);
        func_00206958(self, 0x40000);
        break;

    case 0x52:
        func_001F9FB0(self, 0);
        if (func_001FA2E0(self) != 0) {
            state = func_0023F2D8(self);
            func_00212DD8(self, state);
        }
        f21 = 0.0f;
        f20 = func_001FA308(obj) - 15.0f;
        ev = BtlObjAnim_QueryEvent(*(s32 *)(obj + 0x1530), 2, 0, 1);
        if (f20 < (f32)ev) {
            func_00206958(self, 0x40000);
        }
        break;

    default:
        break;
    }

    if (func_00211310(self, 5, 4) == 0) {
        f21 = 0.0f;
    }
    func_00215068(self, 5, 0xC, D_00385C14, 0.5f);
    func_00215E88(D_00385C18, self, 2);
    func_00216208(self, f21, D_00385C1C);
    func_00216678(self);
    func_002113C0(self, 9, 0x200, 1);
    func_002113C0(self, 0xF, 0x40, 1);
    if (func_00211310(self, 0, 0x100) != 0) {
        func_002113C0(self, 0, 2, 1);
    }
}
