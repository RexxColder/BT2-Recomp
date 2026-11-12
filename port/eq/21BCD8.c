#include "common.h"

extern void BattleSide_SetChara(u8 *obj, s32 idx);
extern s32 func_002113C0(u8 *obj, s32 a1, s32 a2, s32 a3);
extern void func_0020FC38(u8 *obj, s32 a1);

/* 0x0021BCD8: set chara 0x77, run two helper calls, then ++obj->+0x149C and return it. */
s32 func_0021BCD8(u8 *obj) {
    BattleSide_SetChara(obj, 0x77);
    func_002113C0(obj, 0, 2, 1);
    func_0020FC38(obj, 0x2E);
    *(s32 *)(obj + 0x149C) = *(s32 *)(obj + 0x149C) + 1;
    return *(s32 *)(obj + 0x149C);
}
