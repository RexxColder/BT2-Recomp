#include "common.h"

s32 func_00217490(u8 *arg0);
s32 func_00217488(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212DD8(s32 arg0, s32 arg1);
void BattleSide_SetChara(s32 side, s32 chara);
void BtlChar_Vibrate(u8 *chr, f32 power, f32 seconds);
s32 func_0023F410(u8 *arg0);
void func_0020FC38(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00211418(s32 arg0, s32 arg1);
extern f32 D_00386514;
extern f32 D_00386518;
extern f32 D_0038651C;

void func_0022B218(u8 *arg0) {
    s32 v;
    s32 r;

    func_002113C0((s32)arg0, 0, 2, 1);
    v = func_00217490(arg0);
    switch ((u32)(v - 0xF)) {
        case 0:
        case 1:
        case 28:
        case 29:
        case 79:
        case 80:
        case 81:
        case 82:
        case 83:
        case 97:
            goto case_A;
        case 4:
        case 5:
            goto case_E;
        case 59:
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
        case 69:
        case 70:
            goto case_B;
        default:
            goto case_D;
    }

case_B:
    func_00212DD8((s32)arg0, 0x1C);
case_A:
    BattleSide_SetChara((s32)arg0, 0x26);
    BtlChar_Vibrate(arg0, D_00386514, D_00386518);
    r = func_0023F410(arg0);
    if ((r & 0x10) == 0) {
        func_0020FC38((s32)arg0, 0x1C);
    } else {
        func_0020FC38((s32)arg0, 0x1D);
    }
    func_002113C0((s32)arg0, 0xE, 0x200, 1);
    goto case_end;
case_E:
    BattleSide_SetChara((s32)arg0, 0x39);
    goto case_end;
case_D:
    v = func_00217488((s32)arg0);
    if (v == 0x10) {
        BattleSide_SetChara((s32)arg0, 0x23);
        func_00212DD8((s32)arg0, 0x24);
    } else {
        r = *(s32 *)(arg0 + 0xB84);
        if (r > 0) {
            BattleSide_SetChara((s32)arg0, 0x23);
        } else {
            BattleSide_SetChara((s32)arg0, 0x39);
        }
    }
case_end:
    v = func_00217488((s32)arg0);
    if (v == 0x10) {
        func_00211418((s32)arg0, 0x40);
    } else {
        func_00215068((s32)arg0, 0, 0xC, D_0038651C, 0.0f);
        func_00211418((s32)arg0, 0x80);
    }
}
