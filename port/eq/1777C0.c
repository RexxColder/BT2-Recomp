#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
void BtlCharApi_GetFrameMove(s32 arg0, s32 arg1);
s32 rand(void);
void func_00129BB8(s32 arg0, s32 arg1, f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384988;
extern f32 D_0038498C;
extern f32 D_00384990;
extern f32 D_00384994;

/* 0x001777C0 (EftSpdLine_StepTrail in BT3, exact): a trail p with flags word +0x40 bit 1 moves with its fighter (object
 * id word +0x30): pos (+0) += move * height * 0.05 * 0.2; tail (+0x10) = pos + move * -((rand / RAND_MAX * 0.8 + 0.8)
 * * height * 0.05); life (+0x3C) -= 1. Returns 1 when life <= 0 (life then becomes 0), else 0. */
s32 EftSpdLine_StepTrail(u8 *arg0) {
    f32 tmp[4];
    f32 move[4];
    f32 unit;
    f32 h;
    f32 scale;
    s32 r;

    if (*(u32 *)(arg0 + 0x40) & 1) {
        unit = D_00384988;
        BtlCharApi_GetFrameMove(*(s32 *)(arg0 + 0x30), (s32)move);
        h = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x30));
        func_00129BB8((s32)tmp, (s32)move, h * unit * D_0038498C);
        func_00129B28((s32)arg0, (s32)arg0, (s32)tmp);
        r = rand();
        h = BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x30));
        scale = (((f32)r / D_00384990) * D_00384994 + D_00384994) * (h * unit);
        func_00129BB8((s32)tmp, (s32)move, -scale);
        func_00129B28((s32)(arg0 + 0x10), (s32)arg0, (s32)tmp);
        *(f32 *)(arg0 + 0x3C) -= 1.0f;
    }
    if (*(f32 *)(arg0 + 0x3C) <= 0.0f) {
        *(f32 *)(arg0 + 0x3C) = 0.0f;
        return 1;
    }
    return 0;
}
