#include "common.h"

s32 func_00217488(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
s32 BtlActB_NextVariant(s32 arg0, s32 arg1);
void BattleSide_SetChara(s32 side, s32 chara);
s32 BtlChar_GetPos(s32 arg0);

void func_0021FEB8(s32 arg0) {
    s32 v;
    s32 r;
    s32 v1;
    s32 a1;
    s32 p;
    s32 q;
    u32 idx;

    v = func_00217488(arg0);
    a1 = 0xAD;
    idx = (u32)(v - 0x8E);
    if (idx < 0x16) {
        switch (idx) {
            case 0:
                if (func_00218838(arg0, 1) != 0) {
                    a1 = BtlActB_NextVariant(arg0, 4) + 0xB1;
                } else {
                    a1 = BtlActB_NextVariant(arg0, 4) + 0xAD;
                }
                break;
            case 1:
                if (func_00218838(arg0, 1) != 0) {
                    a1 = BtlActB_NextVariant(arg0, 4) + 0xB9;
                } else {
                    a1 = BtlActB_NextVariant(arg0, 4) + 0xB5;
                }
                break;
            case 2:
                r = func_00218838(arg0, 1);
                v1 = 0xC2;
                a1 = (r == 0) ? v1 : 0xC0;
                break;
            case 3:
                r = func_00218838(arg0, 1);
                v1 = 0xC3;
                a1 = (r == 0) ? v1 : 0xC0;
                break;
            case 4:
                r = func_00218838(arg0, 1);
                v1 = 0xBF;
                a1 = (r == 0) ? v1 : 0xC0;
                break;
            case 5:
                r = func_00218838(arg0, 1);
                v1 = 0xC1;
                a1 = (r == 0) ? v1 : 0xC0;
                break;
            case 6:
                r = func_00218838(arg0, 1);
                a1 = 0xC0;
                if (r == 0) {
                    a1 = BtlActB_NextVariant(arg0, 2) + 0xC4;
                }
                break;
            case 16:
                a1 = 0xF0;
                break;
            case 20:
                a1 = 0xF1;
                break;
            case 21:
                a1 = 0xF2;
                break;
            default:
                break;
        }
    }

    BattleSide_SetChara(arg0, a1);
    p = BtlChar_GetPos(arg0);
    *(s32 *)((u8 *)p + 0xC0) = 0;
    q = BtlChar_GetPos(arg0);
    *(s32 *)((u8 *)q + 0xC4) = 0;
}
