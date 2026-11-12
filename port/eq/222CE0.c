#include "common.h"

s32 func_00218838(s32 arg0, s32 arg1);
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
f32 atan2f(f32 farg0, f32 farg1);
void func_002100C0(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212DD8(s32 arg0, s32 arg1);
void func_00215E30(s32 arg0, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
extern f32 D_0038605C;
extern f32 D_00386060;
extern f32 D_00386064;

void func_00222CE0(s32 arg0) {
    s32 var_a1;
    s32 p1;
    s32 p2;
    s32 p;
    f32 ang;

    if (func_00218838(arg0, 0) != 0) {
        p1 = BtlChar_GetPos(arg0);
        p2 = BtlChar_GetPos(arg0);
        ang = atan2f(*(f32 *)p1, *(f32 *)(p2 + 8));
        func_00215E30(arg0, ang, 0.0f);
        func_00215E88(D_0038605C, arg0, 4);
        var_a1 = 0xE2;
    } else {
        p1 = BtlChar_GetPos(arg0);
        p2 = BtlChar_GetPos(arg0);
        ang = atan2f(-*(f32 *)p1, -*(f32 *)(p2 + 8));
        func_00215E30(arg0, ang, 0.0f);
        func_00215E88(D_00386060, arg0, 2);
        var_a1 = 0xE1;
    }
    BattleSide_SetChara(arg0, var_a1);
    p = BtlChar_GetPos(arg0);
    *(f32 *)(p + 0xC0) = D_00386064;
    func_00212DD8(arg0, 0);
    func_002100C0(arg0, 9);
    func_002113C0(arg0, 0, 2, 1);
}
