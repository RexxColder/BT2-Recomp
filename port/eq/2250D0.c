#include "common.h"

extern void BattleSide_SetChara(s32 arg0, s32 arg1);
extern void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 *BtlChar_GetPos(s32 arg0);

void func_002250D0(s32 self) {
    u8 *pos;

    BattleSide_SetChara(self, 0x19D);
    func_002113C0(self, 9, 0x1000000, 1);
    func_002113C0(self, 1, 0x20000, 1);
    pos = BtlChar_GetPos(self);
    *(s32 *)(pos + 0xC0) = 0;
    pos = BtlChar_GetPos(self);
    *(s32 *)(pos + 0xC4) = 0;
}
