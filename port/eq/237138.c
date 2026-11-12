#include "common.h"

s32 func_00217488(s32 arg0);
void func_00217CB8(s32 arg0);
void BattleSide_SetChara(s32 arg0, s32 arg1);

/* 0x00237138(obj): r = func_00217488(obj). r == 0x7E calls BattleSide_SetChara(obj, 0xA3); r == 0x82 calls
 * BattleSide_SetChara(obj, 0x19F). Then func_00217CB8(obj) and the word at obj+0x144C is incremented. */
void func_00237138(u8 *arg0) {
    s32 r = func_00217488((s32)arg0);

    if (r == 0x7E) {
        BattleSide_SetChara((s32)arg0, 0xA3);
    } else if (r == 0x82) {
        BattleSide_SetChara((s32)arg0, 0x19F);
    }
    func_00217CB8((s32)arg0);
    *(s32 *)(arg0 + 0x144C) = *(s32 *)(arg0 + 0x144C) + 1;
}
