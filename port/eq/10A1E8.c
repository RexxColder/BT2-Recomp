#include "common.h"

s32 BattleResult_GetWinnerSide(void);
void Ramp_Start(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
s32 func_00105E18(s32 arg0, s32 arg1);
void func_0010B428(void);
void func_0010B490(void);
void func_0010B638(void);
void func_0010B658(void);
s32 func_0020B328(s32 arg0);
s32 rand(void);
extern u8 *D_003876A0;
extern s32 *D_00387A40;

s32 func_0010A1E8(s32 arg0) {
    s32 winner;
    s32 temp_s2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s5;
    s32 temp_s6;
    s32 temp_idx;
    s32 temp_r;
    s32 var_v0_2;
    s32 var_v0_3;

    winner = BattleResult_GetWinnerSide();
    temp_s2 = (winner == 0);
    temp_a0 = winner * 0x18580;
    temp_v1 = *D_00387A40;
    temp_a1 = temp_s2 * 0x18580;
    temp_s4 = temp_v1 + temp_a0;
    temp_s5 = temp_a1 + temp_v1;
    temp_s6 = *(s32 *)(temp_s4 + 0x97C);
    temp_s3 = *(s32 *)(temp_s5 + 0x97C);
    if (func_00105E18(temp_a0, temp_a1) == 0) {
        *(s8 *)(arg0 + 9) = temp_s2;
        var_v0_3 = 0x16;
        if (func_0020B328(temp_s2) == 0) {
            var_v0_3 = *(u16 *)(temp_s5 + 4);
        }
        *(u16 *)(arg0 + 0x10) = var_v0_3;
        *(s8 *)(arg0 + 8) = 0;
        *(s16 *)(arg0 + 0xC) = 0x2A;
        func_0010B490();
    } else {
        if ((temp_s6 != 0) && (temp_s3 != 0) && (func_0020B328(winner) == 0)) {
            if (func_0020B328(temp_s2) == 0) {
                *(s8 *)(arg0 + 9) = winner;
                temp_idx = *(s32 *)(temp_s5 + 4) * 8 + temp_s6;
                if (*(s16 *)(temp_idx + 4) != -1) {
                    *(u16 *)(arg0 + 0x10) = *(u16 *)(temp_s4 + 4);
                    *(s8 *)(arg0 + 8) = 0;
                    temp_idx = *(s32 *)(temp_s5 + 4) * 8 + temp_s6;
                    var_v0_2 = *(u16 *)(temp_idx + 4) + 0x1E;
                } else {
                    goto block_15;
                }
            } else {
                goto block_9;
            }
        } else {
block_9:
            *(s8 *)(arg0 + 9) = winner;
            var_v0_3 = 0x16;
            if (func_0020B328(winner) == 0) {
block_15:
                var_v0_3 = *(u16 *)(temp_s4 + 4);
            }
            *(u16 *)(arg0 + 0x10) = var_v0_3;
            temp_r = rand();
            *(s8 *)(arg0 + 8) = 0;
            var_v0_2 = (temp_r % 2) + 3;
        }
        *(s16 *)(arg0 + 0xC) = var_v0_2;
        func_0010B428();
    }
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x200;
    Ramp_Start(arg0 + 0x14, (s32)D_003876A0, 10.0f, 0.0f, 1.0f);
    func_0010B658();
    func_0010B638();
    return 1;
}
