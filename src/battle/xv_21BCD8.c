#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* BattleSide_SetChara(arg0, 0x77); func_002113C0(arg0, 0, 2, 1); func_0020FC38(arg0, 0x2E); ++obj->+0x149C */
void func_0021BCD8(s32 arg0) {
    BattleSide_SetChara(arg0, 0x77);
    func_002113C0(arg0, 0, 2, 1);
    func_0020FC38(arg0, 0x2E);
    *(s32 *)((u8 *)arg0 + 0x149C) = *(s32 *)((u8 *)arg0 + 0x149C) + 1;
}
