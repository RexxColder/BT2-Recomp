#include "common.h"

s32 BattleResult_GetWinnerSide(void);
s32 BattleResult_IsKo(void);
s32 BattleResult_IsReasonBit2(void);
void Ramp_Start(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
s32 func_00105EE0(void);
void func_0010B1E8(void);
void func_0010B278(void);
void func_0010B308(void);
void func_0010B398(void);
extern u8 *D_003876A0;

s32 func_0010A750(s32 arg0) {
    u8 *s0;
    s32 w;

    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x200;
    Ramp_Start(arg0 + 0xC, (s32)D_003876A0, 3.5f, 0.0f, 1.0f);
    if (BattleResult_IsKo() != 0) {
        s0 = D_003876A0;
        w = BattleResult_GetWinnerSide();
        if (*(s64 *)(s0 + w * 8 + 0x488) & ((s64)0x8000 << 35)) {
            func_0010B278();
        } else {
            func_0010B1E8();
        }
    } else if (BattleResult_IsReasonBit2() != 0) {
        func_0010B308();
    } else if (func_00105EE0() != 0) {
        func_0010B398();
    }
    return 1;
}
