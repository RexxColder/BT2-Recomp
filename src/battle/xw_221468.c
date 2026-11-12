#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
f32 BtlMember_GetHealthRatio(s32 arg0);
void func_0020FC38(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212878(void);
s32 func_00218838(s32 arg0, s32 arg1);

// Setup for battle object arg0: side chara 0xD3 or 0xD2 by func_00218838(arg0, 1), func_002113C0(arg0, 0, 2, 1), the word
// at +0x8C0 is 50 (int), replaced by (1 - health ratio) * 50 when func_00212878 is nonzero; clears the word at +0xC4 of
// BtlChar_GetPos(arg0), then func_0020FC38(arg0, 0x48).
void func_00221468(s32 arg0) {
    if (func_00218838(arg0, 1) != 0) {
        BattleSide_SetChara(arg0, 0xD3);
    } else {
        BattleSide_SetChara(arg0, 0xD2);
    }
    func_002113C0(arg0, 0, 2, 1);
    *(s32 *)((u8 *)arg0 + 0x8C0) = 0x32;
    if (func_00212878() != 0) {
        *(s32 *)((u8 *)arg0 + 0x8C0) = (s32)((1.0f - BtlMember_GetHealthRatio(arg0)) * 50.0f);
    }
    *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC4) = 0;
    func_0020FC38(arg0, 0x48);
}
