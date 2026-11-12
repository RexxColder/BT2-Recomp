#include "common.h"

s32 Ramp_Step(u8 *arg0);
s32 BattleResult_HasWinner(void);

s32 func_0010A840(u8 *arg0) {
    if (Ramp_Step(arg0 + 0xC) == 0) {
        return 4;
    }
    if (BattleResult_HasWinner() == 0) {
        return 6;
    }
    return 5;
}
