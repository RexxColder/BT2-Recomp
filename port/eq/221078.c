#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_00218838(u8 *arg0, s32 arg1);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);
f32 BtlUtil_WrapAngle(f32 arg0, u8 *arg1);
extern f32 D_00385F90;

void func_00221078(u8 *arg0) {
    BattleSide_SetChara((s32)arg0, 0xED);
    if (func_00218838(arg0, 1) != 0) {
        func_00215E30((s32)arg0, *(f32 *)(arg0 + 0xB5C), 0.0f);
        return;
    }
    func_00215E30((s32)arg0, BtlUtil_WrapAngle(*(f32 *)(arg0 + 0xB5C) + D_00385F90, arg0), 0.0f);
}
