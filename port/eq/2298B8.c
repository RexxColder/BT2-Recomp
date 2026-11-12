#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
u8 *BtlChar_GetPos(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00217490(s32 arg0);
extern f32 D_0038643C;

void func_002298B8(s32 arg0) {
    if (*(f32 *)(BtlChar_GetPos(arg0) + 0xC4) < 0.0f) {
        BattleSide_SetChara(arg0, 0x2C);
    } else {
        BattleSide_SetChara(arg0, 0x2D);
    }
    if ((func_00217490(arg0) != 9) && (BtlPad_Test48(arg0, 8) != 0)) {
        func_00215068(arg0, 0, 0xC, D_0038643C, 0.0f);
    }
    func_002113C0(arg0, 0, 2, 0);
}
