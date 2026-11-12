#include "m2c_macros.h"

s32 BattleResult_HasWinner(void);
s32 Ramp_Step(s32);

// Result code of a ramp step: 4 while Ramp_Step(arg0+0xC) reports 0; otherwise 6 or 5 depending on whether BattleResult_HasWinner is 0.
s32 func_0010A840(s32 arg0) {
    if (Ramp_Step(arg0 + 0xC) != 0) {
        return (BattleResult_HasWinner() != 0) ? 5 : 6;
    }
    return 4;
}
