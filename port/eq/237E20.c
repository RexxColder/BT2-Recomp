#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void BtlAnim_SetBlend(s32 arg0, f32 farg0);
void BtlAnim_SetNoBlend(s32 arg0, f32 farg0);
void func_001F9E38(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00212DD8(s32 arg0, s32 arg1);
extern f32 D_00386A84;

void func_00237E20(u8 *arg0) {
    BattleSide_SetChara((s32)arg0, 0xA5);
    if (*(u8 *)(arg0 + 0xB55) != 0) {
        BtlAnim_SetNoBlend((s32)arg0, D_00386A84);
    } else {
        BtlAnim_SetBlend((s32)arg0, D_00386A84);
        func_001F9E38((s32)arg0, 0x34);
    }
    func_00212DD8((s32)arg0, 7);
    func_002113C0((s32)arg0, 0, 2, 1);
    func_002113C0((s32)arg0, 0x10, 0x20000, 1);
    *(s32 *)(arg0 + 0x1450) = *(s32 *)(arg0 + 0x1450) + 1;
}
