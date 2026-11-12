#include "common.h"

extern void BattleSide_SetChara(u8 *obj, s32 idx);
extern s32 func_00240398(u8 *obj);
extern s32 func_00203888(u8 *obj, s32 a1, s32 a2);
extern u8 *BtlChar_GetPos(u8 *obj);
extern void func_00211418(u8 *obj, s32 flags);

/* 0x00226838: set chara 0x86, func_00203888(obj, func_00240398(obj), 0), zero pos +0xC0 and +0xC4, tail call func_00211418(obj, 0x8000). */
void func_00226838(u8 *obj) {
    BattleSide_SetChara(obj, 0x86);
    func_00203888(obj, func_00240398(obj), 0);
    *(s32 *)(BtlChar_GetPos(obj) + 0xC0) = 0;
    *(s32 *)(BtlChar_GetPos(obj) + 0xC4) = 0;
    func_00211418(obj, 0x8000);
}
