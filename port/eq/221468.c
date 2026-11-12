#include "common.h"

extern s32 func_00218838(u8 *arg0, s32 arg1);
extern void BattleSide_SetChara(u8 *arg0, s32 arg1);
extern void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00212878(void);
extern f32 BtlMember_GetHealthRatio(u8 *arg0);
extern u8 *BtlChar_GetPos(u8 *arg0);
extern void func_0020FC38(u8 *arg0, s32 arg1);

void func_00221468(u8 *arg0) {
    if (func_00218838(arg0, 1) != 0) {
        BattleSide_SetChara(arg0, 0xD3);
    } else {
        BattleSide_SetChara(arg0, 0xD2);
    }
    func_002113C0(arg0, 0, 2, 1);
    *(s32 *)(arg0 + 0x8C0) = 0x32;
    if (func_00212878() != 0) {
        f32 ratio = BtlMember_GetHealthRatio(arg0);
        *(s32 *)(arg0 + 0x8C0) = (s32)((1.0f - ratio) * 50.0f);
    }
    *(s32 *)(BtlChar_GetPos(arg0) + 0xC4) = 0;
    func_0020FC38(arg0, 0x48);
}
