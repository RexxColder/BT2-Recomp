#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00240398(s32 arg0);
void func_00203888(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_003862B0;
extern f32 D_003862B4;
extern f32 D_003862B8;
extern f32 D_003862BC;

void func_00226D28(s32 arg0) {
    s32 var_a1;
    s32 var_s1;
    f32 temp_f0;

    var_s1 = 0x83;
    temp_f0 = BtlUtil_WrapAngle(*(f32 *)(arg0 + 0x150) - *(f32 *)(BtlChar_GetPos(arg0) + 0x14));
    var_a1 = 0x83;
    if (!(temp_f0 < D_003862B0)) {
        if (temp_f0 < D_003862B4) {
            var_s1 = 0x85;
        } else if (temp_f0 < D_003862B8) {
            if (func_00211310(arg0, 0, 1) != 0) {
                *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 1;
                func_002113C0(arg0, 0, 2, 1);
            }
        } else if (temp_f0 < D_003862BC) {
            var_s1 = 0x84;
        }
        var_a1 = var_s1;
    }
    BattleSide_SetChara(arg0, var_a1);
    if (func_00211310(arg0, 1, 4) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    func_00203888(arg0, func_00240398(arg0), 0);
    func_00211418(arg0, 0x8000);
}
