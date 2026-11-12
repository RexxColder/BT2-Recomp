#include "common.h"

void BattleSide_SetChara(void *arg0, s32 arg1);
void *BtlChar_GetPos(void *arg0);
f32 BtlUtil_WrapAngle(f32 arg0);
f32 atan2f(f32 arg0, f32 arg1);
f32 func_00207E88(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(s32 arg0, s32 arg1, f32 farg2);
s32 func_0023F410(s32 arg0);
f32 sinf(f32 arg0);

void func_002289D0(void *arg0) {
    s32 var_s0;
    s32 temp_r2;
    u8 *temp_s0;
    u8 *temp_v0_2;

    var_s0 = 0xB;
    if (!(func_00207E88((s32)arg0) < 0.0f)) {
        var_s0 = 0xE;
    }
    if ((func_0023F410((s32)arg0) & 0x1000) && (func_00211310((s32)arg0, 0, 2) != 0)) {
        temp_r2 = func_00211310((s32)arg0, 0, 0x100);
        var_s0 = (temp_r2 == 0) ? 0x1A4 : var_s0;
    }
    BattleSide_SetChara(arg0, var_s0);
    func_00215E88((s32)arg0, 0, 1.0f);
    if (var_s0 != 0x1A4) {
        temp_s0 = (u8 *)BtlChar_GetPos(arg0);
        temp_v0_2 = (u8 *)BtlChar_GetPos(arg0);
        *(f32 *)((u8 *)arg0 + 0x8D0) =
            sinf(BtlUtil_WrapAngle(atan2f(*(f32 *)(temp_s0 + 0x20), *(f32 *)(temp_v0_2 + 0x28))
                                   - *(f32 *)((u8 *)arg0 + 0x150)));
    }
}
