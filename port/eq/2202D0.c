#include "common.h"

s32 func_00217488(void *a0);
s32 func_00218838(void *a0, s32 a1, s32 a2);
void BattleSide_SetChara(void *a0, s32 a1);
void *BtlChar_GetPos(void *a0);

void func_002202D0(void *arg0) {
    s32 v1;
    s32 r;
    s32 s1;
    void *pA;
    void *pB;

    v1 = func_00217488(arg0);
    s1 = 0xBD;
    if (v1 == 0x9C) {
        r = func_00218838(arg0, 1, v1 < 0x9D);
        if (r != 0) {
            s1 = 0xBE;
        }
    } else if (v1 < 0x9D) {
        if (v1 == 0x81) {
            s1 = 0xAB;
        }
    } else {
        if (v1 == 0x9D) {
            s1 = 0xC7;
        }
    }
    BattleSide_SetChara(arg0, s1);
    pA = BtlChar_GetPos(arg0);
    *(s32 *)((u8 *)pA + 0xC0) = 0;
    pB = BtlChar_GetPos(arg0);
    *(s32 *)((u8 *)pB + 0xC4) = 0;
}
