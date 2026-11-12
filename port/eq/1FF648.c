#include "common.h"

s32 BattleResult_GetFlags(u8 *arg0);
s32 func_001FE0F8(u8 *arg0, s32 arg1);
s32 func_001FE1E8(u8 *arg0, s32 arg1);
s32 func_001FE498(u8 *arg0, s32 arg1);
s32 func_001FF008(u8 *arg0, s32 arg1);
s32 func_001FF478(u8 *arg0, s32 arg1);
void func_00203310(u8 *arg0, s32 arg1, s32 arg2);
f32 func_00210A98(u8 *arg0, s32 arg1);
s32 func_00210DD8(u8 *arg0);
u8 *func_00211288(s32 arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023E520(u8 *arg0);
s32 func_0023EBD8(u8 *arg0);
extern f32 D_0038587C;

void func_001FF648(u8 *arg0) {
    s32 var_s1;
    s32 var_s2;
    u8 *var_s3;
    u8 *var_s4;

    var_s4 = arg0 + 0xBE0;
    if (func_00211310(arg0, 4, 1) != 0) {
        return;
    }
    if (func_0023E520(arg0) == -1) {
        return;
    }
    if (!(*(s32 *)(*(u8 **)(arg0 + 0x1530) + 0xE50) & 0x0F000000)) {
        if (func_00211310(arg0, 4, 0x40) == 0) {
            return;
        }
    }

    var_s1 = func_00210DD8(arg0);
    var_s3 = func_00211288(var_s1);
    if (func_00211310(var_s3, 3, 1) == 0) {
        var_s2 = 0;
        if (fabsf(func_00210A98(arg0, 4)) < D_0038587C) {
            var_s2 = 1;
        }
        var_s2 = (BattleResult_GetFlags(arg0) & 8) ? 1 : var_s2;
        if (var_s2 != 0) {
            func_002113C0(arg0, 4, 1, 1);
            if ((func_001FE0F8(arg0, var_s1) == 0) || (func_001FE1E8(arg0, var_s1) == 0) ||
                (func_001FE498(arg0, var_s1) == 0)) {
                func_002113C0(arg0, 4, 8, 1);
                return;
            }
            if (func_001FF008(arg0, var_s1) != 0) {
                if (func_001FF478(arg0, var_s1) != 0) {
                    *(s32 *)(var_s4 + 0x10) = var_s1;
                }
                return;
            }
            func_00203310(var_s3, func_0023EBD8(arg0), 0xC);
        }
    } else {
        func_002113C0(arg0, 4, 1, 1);
        func_002113C0(arg0, 4, 8, 1);
    }
}
