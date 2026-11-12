#include "common.h"

s32 BattleResult_IsAborted(s32 arg0); /* GUESS arity: asm passes a0 = arg0 through */
s32 func_00284E68(s32 arg0, s32 arg1, f32 farg0);
f32 Ramp_Start(s32 arg0, f32 farg0, f32 farg1, f32 farg2);
extern f32 D_00383E20;
extern u8 *D_003876A0;

s32 func_0010A9D8(u8 *arg0) {
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x200;
    if (BattleResult_IsAborted((s32)arg0) != 0) {
        goto block_5;
    }
    if (*(s32 *)(D_003876A0 + 0xB8) == 0) {
        arg0[8] = 0;
    } else {
block_5:
        func_00284E68(0, 0, 1.0f);
        Ramp_Start((s32)(arg0 + 0xC), D_00383E20, 0.0f, 1.0f);
        arg0[8] = 1;
    }
    return 1;
}
