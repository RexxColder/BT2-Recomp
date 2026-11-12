#include "common.h"

s32 func_00217488(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00212320(s32 arg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
s32 func_00241F80(s32 arg0, s32 arg1);
void func_0023AAA0(s32 arg0);
extern f32 D_00386BEC;
extern f32 D_00386BF0;

void func_0023B1B8(s32 arg0) {
    u8 *p = (u8 *)arg0;
    s32 var_a1;
    s32 temp_v0;

    temp_v0 = func_00217488(arg0);
    if (temp_v0 == 0xDA) {
        func_00206958(arg0, (s64)0x8000 << 36);
        func_002113C0(arg0, 0xF, 0x400, 1);
        var_a1 = 0x11A;
    } else if (temp_v0 == 0xDB) {
        func_00206958(arg0, (s64)0x8000 << 37);
        func_002113C0(arg0, 0xF, 0x800, 1);
        var_a1 = 0x11B;
    } else {
        var_a1 = 0x11A;
    }
    BattleSide_SetChara(arg0, var_a1);
    if (!(func_00241F80(arg0, func_00212320(arg0)) & 0x80)) {
        func_0023AAA0(arg0);
    }
    if (func_00211310(arg0, 0, 1) != 0) {
        if (func_00241F80(arg0, func_00212320(arg0)) & 2) {
            func_00215068(arg0, 1, 0xD, D_00386BEC, 0.0f);
        }
        if (func_00241F80(arg0, func_00212320(arg0)) & 4) {
            func_00215068(arg0, 1, 0xD, D_00386BF0, 1.0f);
        }
    }
    *(s32 *)(p + 0xA30) = 0;
    *(f32 *)(p + 0x8D0) = *(f32 *)(p + 0xAC4);
    func_00211418(arg0, 0x40000);
}
