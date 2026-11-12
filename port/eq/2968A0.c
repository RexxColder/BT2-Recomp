#include "common.h"

void Mat3_MulVecRows(s32 arg0, s32 arg1, s32 arg2);

void Rigid_UpdateCenter(u8 *arg0) {
    Mat3_MulVecRows((s32)(arg0 + 0x30), (s32)(arg0 + 0x20), (s32)(arg0 + 0x50));
    *(f32 *)(arg0 + 0x30) = *(f32 *)(arg0 + 0x30) + *(f32 *)(arg0 + 0x40);
    *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x34) + *(f32 *)(arg0 + 0x44);
    *(f32 *)(arg0 + 0x38) = *(f32 *)(arg0 + 0x38) + *(f32 *)(arg0 + 0x48);
}
