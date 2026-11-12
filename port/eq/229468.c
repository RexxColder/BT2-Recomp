#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void BtlAnim_SetNoBlend(s32 arg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211418(s32 arg0, s32 arg1);
extern f32 D_0038640C;

s32 func_00229468(s32 arg0) {
    BattleSide_SetChara(arg0, 0x2B);
    func_002113C0(arg0, 0, 2, 0);
    BtlAnim_SetNoBlend(arg0);
    func_00215068(arg0, 0, 0xC, D_0038640C, 0.0f);
    func_0020FC38(arg0, 0x31);
    return func_00211418(arg0, 0x20);
}
