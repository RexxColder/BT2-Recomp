#include "common.h"
void bt2_fightlog_note(const char *fmt, ...);

void BattleSide_SetChara(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0022C9B8(u8 *arg0) {
    BattleSide_SetChara((s32)arg0, 0x3D);
    func_002113C0((s32)arg0, 0, 2, 1);
    if (*(s32 *)(arg0 + 0xB84) > 0) {
        *(s32 *)(arg0 + 0x8DC) = *(s32 *)(arg0 + 0x8DC) | 2;
        bt2_fightlog_note("B3 BIT2 22C9B8 chr %08X B84 %d", (s32)arg0, *(s32 *)(arg0 + 0xB84)); /* TEMP */
    }
}
