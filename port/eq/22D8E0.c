#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void BtlOpp_GetDelta(s32 arg0, s32 arg1);
void func_002109C8(s32 arg0, s32 arg1);
f32 BtlOpp_GetHalfHeightDiff(s32 arg0);
f32 BtlMove_CalcVerticalSpeed(f32 farg0, f32 farg1);
s32 BtlChar_GetPos(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0022D8E0(s32 arg0) {
    s32 sp[8];
    f32 temp_f20;
    f32 temp_h;

    BattleSide_SetChara(arg0, 0x27);
    func_0020FC38(arg0, 0x1F);
    BtlOpp_GetDelta(arg0, (s32)sp);
    func_002109C8(arg0, (s32)&sp[4]);
    temp_h = BtlOpp_GetHalfHeightDiff(arg0);
    temp_f20 = BtlMove_CalcVerticalSpeed(*(f32 *)&sp[1] + temp_h, *(f32 *)&sp[5] * 0.5f);
    *(f32 *)(BtlChar_GetPos(arg0) + 0xC4) = temp_f20;
    func_002113C0(arg0, 0, 2, 1);
}
