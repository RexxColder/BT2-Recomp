#include "m2c_macros.h"

void *BtlChar_GetPos();                          /* extern */
extern f32 D_00385AC8;
extern f32 D_00385ACC;

void func_00216770(s32 arg0) {
    f32 temp_f20;
    void *temp_s0;
    void *temp_v0;

    temp_v0 = BtlChar_GetPos(arg0);
    temp_f20 = D_00385ACC;
    M2C_FIELD(temp_v0, f32 *, 0xC4) = (f32) (M2C_FIELD(temp_v0, f32 *, 0xC4) + D_00385AC8);
    if (temp_f20 < M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC4)) {
        M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC4) = temp_f20;
    }
    temp_s0 = BtlChar_GetPos(arg0);
    M2C_FIELD(temp_s0, f32 *, 4) = (f32) (M2C_FIELD(temp_s0, f32 *, 4) + M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC4));
}
