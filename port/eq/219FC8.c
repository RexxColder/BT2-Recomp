#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_001F9D78(s32 arg0, s32 arg1);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA2E0(s32 arg0);
f32 func_001FA308(s32 arg0);
f32 func_001FA318(s32 arg0);
void func_00206958(s32 arg0, s64 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212DD8(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002182A8(s32 arg0);
void func_002188C8(s32 arg0);
s32 func_0023F2D8(s32 arg0);
extern f32 D_00385BF0;
extern f32 D_00385BF4;
extern f32 D_00385BF8;
extern f32 D_00385BFC;
extern f32 D_00385C00;

void func_00219FC8(s32 arg0) {
    f32 f20;
    f32 f21;
    s32 v;
    s32 a1;
    s32 done;

    v = BtlObjXf_Update(arg0);
    f21 = D_00385BF0;
    /* case result: 0 = fall to tail with a1 = 5; 1 = block_25 (206958 0x40000) then tail */
    done = 0;
    switch (v) {
    case 0x4D:
        func_002188C8(arg0);
        func_001FA0A0(arg0, 0x4E, 0);
        break;
    case 0x4E:
        func_002188C8(arg0);
        if (func_001FA0A0(arg0, 0x4F, 0) == 0) {
            if (BtlPad_Test48(arg0, 1) == 0) {
                func_001F9D78(arg0, 0x4F);
            }
            if (BtlPad_Test4C(arg0, 3) != 0 || BtlPad_Test4C(arg0, 2) != 0 ||
                BtlPad_Test4C(arg0, 0) != 0) {
                func_001F9D78(arg0, 0x39);
                func_002182A8(arg0);
                func_0020FC38(arg0, 0x1F);
                *(s32 *)(arg0 + 0x14A0) = *(s32 *)(arg0 + 0x14A0) + 1;
            }
        } else {
            BtlChar_SetVibration(arg0, 1.0f, D_00385BF4);
        }
        *(f32 *)(arg0 + 0x9B0) = func_001FA318(arg0);
        done = 1;
        break;
    case 0x4F:
        func_001F9FB0(arg0, 0);
        if (func_001FA2E0(arg0) != 0) {
            func_00212DD8(arg0, func_0023F2D8(arg0));
        }
        f21 = 0.0f;
        f20 = func_001FA308(arg0) - 15.0f;
        if (f20 < (f32)BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 2, 0, 1)) {
            done = 1;
        }
        break;
    case 0x39:
        func_001F9FB0(arg0, 0);
        f21 = 0.0f;
        func_002113C0(arg0, 5, 0x800, 1);
        break;
    default:
        break;
    }
    if (done) {
        func_00206958(arg0, 0x40000);
    }
    a1 = 5;
    if (func_00211310(arg0, a1, 4) == 0) {
        f21 = 0.0f;
    }
    func_00215068(arg0, 5, 0xC, D_00385BF8, 0.5f);
    func_00215E88(D_00385BFC, arg0, 2);
    func_00216208(arg0, f21, D_00385C00);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 0xF, 0x40, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
