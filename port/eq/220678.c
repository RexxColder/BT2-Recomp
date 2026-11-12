#include "common.h"

extern f32 D_00385F28;

s32 func_00217488(u8 *arg0);
s32 func_00218838(u8 *arg0, s32 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
u8 *BtlChar_GetPos(u8 *arg0);
f32 BtlUtil_WrapAngle(f32 arg0);

void func_00220678(u8 *arg0) {
    s32 r;
    s32 s2;
    s32 v;
    u8 *pA;
    u8 *pB;
    u8 *pC;
    u8 *pD;
    u8 *pE;
    u8 *pF;
    f32 f20;
    f32 f12;
    f32 w;

    s2 = 0;
    r = func_00217488(arg0);

    if (r == 0x98) {
        v = func_00218838(arg0, 1);
        s2 = 0xD4;
        if (v != 0) {
            f20 = D_00385F28;
            pA = BtlChar_GetPos(arg0);
            pB = BtlChar_GetPos(arg0);
            f12 = *(f32 *)(pB + 0x14) + f20;
            w = BtlUtil_WrapAngle(f12);
            *(f32 *)(pA + 0x14) = w;
            pC = BtlChar_GetPos(arg0);
            pD = BtlChar_GetPos(arg0);
            f12 = *(f32 *)(pD + 0xB4) + f20;
            w = BtlUtil_WrapAngle(f12);
            *(f32 *)(pC + 0xB4) = w;
            pE = BtlChar_GetPos(arg0);
            pF = BtlChar_GetPos(arg0);
            *(f32 *)(pE + 0xB0) = -*(f32 *)(pF + 0xB0);
        }
        func_002113C0(arg0, 0, 2, 0);
        BattleSide_SetChara(arg0, s2);
        return;
    }

    if (r < 0x99) {
        if (r == 0x97) {
            v = func_00218838(arg0, 1);
            s2 = (v == 0) ? 0xCA : 0xCB;
            func_002113C0(arg0, 0, 2, 0);
            BattleSide_SetChara(arg0, s2);
            return;
        }
        BattleSide_SetChara(arg0, 0);
        return;
    }

    if (r == 0xA4) {
        v = func_00218838(arg0, 1);
        s2 = (v == 0) ? 0x193 : 0x194;
        BattleSide_SetChara(arg0, s2);
        return;
    }
    BattleSide_SetChara(arg0, 0);
}
