#include "common.h"

s32 func_003126C8(s32 arg0, s32 arg1);
void Mat3_MulVecRows(s32 arg0, s32 arg1, s32 arg2);
void Mat3_MulVecCols(s32 arg0, s32 arg1, s32 arg2);

void Rigid_SetVelocity(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 sp[12];
    u8 *s1;

    s1 = arg0 + 0x50;
    func_003126C8((s32)&sp[8], (s32)arg2);
    Mat3_MulVecRows((s32)sp, (s32)&sp[8], (s32)s1);
    Mat3_MulVecCols((s32)&sp[4], (s32)sp, (s32)s1);
    sp[8] = 0.0f;
    sp[10] = 0.0f;
    *(f32 *)(arg0 + 0xD0) = *(f32 *)(arg0 + 0xD0) - sp[4];
    *(f32 *)(arg0 + 0xD4) = *(f32 *)(arg0 + 0xD4) - sp[5];
    *(f32 *)(arg0 + 0xD8) = *(f32 *)(arg0 + 0xD8) - sp[6];
    sp[9] = *(f32 *)(arg2 + 4);
    Mat3_MulVecCols((s32)&sp[4], (s32)&sp[8], (s32)s1);
    *(f32 *)(arg0 + 0xD0) = *(f32 *)(arg0 + 0xD0) + sp[4];
    *(f32 *)(arg0 + 0xD4) = *(f32 *)(arg0 + 0xD4) + sp[5];
    *(f32 *)(arg0 + 0xD8) = *(f32 *)(arg0 + 0xD8) + sp[6];
    *(f32 *)(arg0 + 0x90) = *(f32 *)(arg1 + 0);
    *(f32 *)(arg0 + 0x94) = *(f32 *)(arg1 + 4);
    *(f32 *)(arg0 + 0x98) = *(f32 *)(arg1 + 8);
}
