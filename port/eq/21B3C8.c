#include "common.h"

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_00217CB8(s32 arg0);
u8 *BtlChar_GetPos(s32 arg0);
extern f32 D_00385C8C;

u8 *func_0021B3C8(s32 arg0) {
    u8 *pos;
    BattleSide_SetChara(arg0, 0x53);
    func_00217CB8(arg0);
    pos = BtlChar_GetPos(arg0);
    *(f32 *)(pos + 0xC0) = D_00385C8C;
    return pos;
}
