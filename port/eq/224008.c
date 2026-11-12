#include "common.h"

extern f32 D_00386124;

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217488(s32 arg0);
s32 func_00217490(s32 arg0);
s32 func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);

/* 0x00224008: menu/side setup. Maps the value of func_00217488 (0x3A..0x40) to a side code
 * (0x100..0x109); code 0x48 case probes BtlPad_Test48 for 0xC..0xF. Then BattleSide_SetChara,
 * a func_00211310 probe (0 returns 0), func_00217490 (0x41 returns 0x41), otherwise a tail call
 * to func_00215068 with a float constant. */
s32 func_00224008(s32 arg0) {
    s32 a1 = 0x100;
    s32 idx = func_00217488(arg0) - 0x3A;
    s32 r;

    if ((u32)idx < 7) {
        switch (idx) {
            case 0:
                r = BtlPad_Test48(arg0, 0xC);
                if (r != 0) {
                    a1 = 0x102;
                    break;
                }
                r = BtlPad_Test48(arg0, 0xD);
                if (r != 0) {
                    a1 = 0x104;
                    break;
                }
                r = BtlPad_Test48(arg0, 0xE);
                if (r != 0) {
                    a1 = 0x106;
                    break;
                }
                r = BtlPad_Test48(arg0, 0xF);
                a1 = (r == 0) ? 0x100 : 0x108;
                break;
            case 1:
                a1 = 0xFD;
                break;
            case 2:
                a1 = 0x103;
                break;
            case 3:
                a1 = 0x105;
                break;
            case 4:
                a1 = 0x107;
                break;
            case 5:
                a1 = 0x109;
                break;
            case 6:
                a1 = 0x101;
                break;
            default:
                break;
        }
    }

    BattleSide_SetChara(arg0, a1);
    if (func_00211310(arg0, 0, 1) == 0) {
        return 0;
    }
    if (func_00217490(arg0) == 0x41) {
        return 0x41;
    }
    /* a0 = arg0 comes from the delay slot of the beq at 0x1240F8 (daddu $a0,$s0,$zero) */
    return func_00215068(arg0, 1, 0xC, D_00386124, 0.0f);
}
