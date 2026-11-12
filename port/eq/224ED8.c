#include "common.h"

void BattleSide_SetChara(u8 *arg0, s32 arg1);
s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
u8 *BtlChar_GetPos(u8 *arg0);

void func_00224ED8(u8 *arg0) {
    u8 *pos;
    u8 *pos2;

    BattleSide_SetChara(arg0, 0x19B);
    func_002113C0(arg0, 9, 0x1000000, 1);
    func_002113C0(arg0, 1, 0x20000, 1);
    pos = BtlChar_GetPos(arg0);
    *(s32 *)(pos + 0xC0) = 0;
    pos2 = BtlChar_GetPos(arg0);
    *(s32 *)(pos2 + 0xC4) = 0;
    *(s32 *)(arg0 + 0xB74) = 0;
}
