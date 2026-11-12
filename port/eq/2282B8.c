#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00211418(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
f32 sinf(f32 farg0);

void func_002282B8(s32 arg0) {
    s32 side;
    s32 p1;
    s32 p2;
    f32 ang;

    side = 2;
    if ((func_0023F410(arg0) & 0x1000) && (func_00211310(arg0, 0, 2) != 0)) {
        side = (func_00211310(arg0, 0, 0x100) == 0) ? 0x1A4 : 2;
    }
    BattleSide_SetChara(arg0, side);
    p1 = BtlChar_GetPos(arg0);
    p2 = BtlChar_GetPos(arg0);
    ang = atan2f(*(f32 *)(p1 + 0x20), *(f32 *)(p2 + 0x28));
    *(f32 *)(arg0 + 0x8D0) = sinf(BtlUtil_WrapAngle(ang - *(f32 *)(arg0 + 0x150)));
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_0020FC38(arg0, 0x38);
    }
    func_00211418(arg0, 1);
}
