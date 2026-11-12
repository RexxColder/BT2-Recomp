#include "common.h"

void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_00211418(u8 *arg0, s32 arg1);
s32 func_00217490(u8 *arg0);

void func_002306F8(u8 *arg0) {
    s32 chara = 0x18A;
    s32 v;

    if (*(s32 *)(arg0 + 0x1534) != 0) {
        chara = 0x18B;
    }
    BattleSide_SetChara(arg0, chara);
    *(s32 *)(arg0 + 0xA3C) = 0;
    func_00211418(arg0, 0x200000);
    v = func_00217490(arg0);
    if (v < 0xC1 && v >= 0xB8) {
        *(s32 *)(arg0 + 0x8DC) |= 1;
    }
}
