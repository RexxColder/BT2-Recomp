#include "common.h"

s32 rand(void);
f32 Ramp_Start(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2);
extern u8 *D_003876A0;
extern u8 *D_00387A40;

s32 func_00109D78(s32 arg0) {
    u8 *temp_s0 = (u8 *)arg0;
    u8 *temp_a1;
    u8 *temp_a2;
    u8 *var_v0;
    s32 temp_a3;
    s32 temp_t0;
    u8 *t1;

    temp_a1 = *(u8 **)D_00387A40;
    temp_a3 = *(s32 *)(temp_a1 + 0x97C);
    temp_a2 = temp_a1 + 0x18580;
    temp_t0 = *(s32 *)(temp_a2 + 0x97C);
    if ((temp_a3 != 0) && (temp_t0 != 0)) {
        t1 = (u8 *)(temp_a3 + *(s32 *)(temp_a2 + 4) * 8);
        if (*(s16 *)(t1 + 0) != -1) {
            if (*(s16 *)(t1 + 2) != 0) {
                *(s8 *)(temp_s0 + 0x9) = 1;
                *(s8 *)(temp_s0 + 0xA) = 0;
                *(u16 *)(temp_s0 + 0x10) = *(u16 *)(temp_a2 + 4);
                *(u16 *)(temp_s0 + 0x12) = *(u16 *)(temp_a1 + 4);
                *(s16 *)(temp_s0 + 0xC) = (s16)(*(u16 *)(u8 *)(temp_t0 + *(s32 *)(temp_a1 + 4) * 8) + 6);
                var_v0 = t1;
            } else {
                *(s8 *)(temp_s0 + 0x9) = 0;
                *(s8 *)(temp_s0 + 0xA) = 1;
                *(u16 *)(temp_s0 + 0x10) = *(u16 *)(temp_a1 + 4);
                *(u16 *)(temp_s0 + 0x12) = *(u16 *)(temp_a2 + 4);
                *(s16 *)(temp_s0 + 0xC) = (s16)(*(u16 *)t1 + 6);
                var_v0 = (u8 *)(temp_t0 + *(s32 *)(temp_a1 + 4) * 8);
            }
            *(s16 *)(temp_s0 + 0xE) = (s16)(*(u16 *)var_v0 + 6);
        } else {
            goto block_10;
        }
    } else {
block_10:
        *(s8 *)(temp_s0 + 0x9) = 0;
        *(s8 *)(temp_s0 + 0xA) = 1;
        *(u16 *)(temp_s0 + 0x10) = *(u16 *)(temp_a1 + 4);
        *(u16 *)(temp_s0 + 0x12) = *(u16 *)(temp_a2 + 4);
        *(s16 *)(temp_s0 + 0xC) = (s16)(rand() % 2);
        *(s16 *)(temp_s0 + 0xE) = (s16)(rand() % 2);
    }
    *(s8 *)(temp_s0 + 0x8) = 0;
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x200;
    Ramp_Start((s32)(temp_s0 + 0x14), 0x200, 10.0f, 0.0f, 1.0f);
    return 1;
}
