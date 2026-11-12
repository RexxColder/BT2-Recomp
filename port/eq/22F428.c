#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_001FA3A8(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00218838(s32 arg0, s32 arg1);
extern f32 D_00386794;
extern f32 D_00386798;

void func_0022F428(s32 arg0) {
    s32 v;

    BtlObjXf_Update(arg0);
    BattleSide_SetChara(arg0, (func_00218838(arg0, 0) == 0) ? 0xFB : 0xFC);
    func_002113C0(arg0, 0, 2, 1);
    if (func_00211310(arg0, 0, 1) != 0) {
        v = func_001FA3A8(BtlObjXf_Update(arg0));
        if (v & 0x01000000) {
            func_00215068(arg0, 2, 0xC, D_00386794, 0.0f);
            return;
        }
        func_00215068(arg0, 1, 0xC, D_00386798, 0.0f);
    }
}
