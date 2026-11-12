#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void BtlMove_BrakeVertical(s32 arg0);
void *BtlChar_GetPos(s32 arg0);
void func_00216770(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00216890(f32 farg0, s32 arg1, f32 farg1);
extern f32 D_00385ABC;
extern f32 D_00385AC0;
extern f32 D_00385AC4;

void func_002166C0(s32 arg0) {
    f32 var_f1;
    u8 *pos;

    if (func_00211310(arg0, 0, 2) != 0) {
        if (func_00211310(arg0, 0, 0x100) != 0) {
            BtlMove_BrakeVertical(arg0);
            return;
        }
        pos = (u8 *)BtlChar_GetPos(arg0);
        var_f1 = (f32)*(s32 *)(pos + 0xDC) * D_00385ABC;
        if (var_f1 > 1.0f) {
            var_f1 = 1.0f;
        }
        func_00216890(var_f1 * D_00385AC4, arg0, D_00385AC0);
        return;
    }
    func_00216770(arg0, 0, 0x100, 0);
}
