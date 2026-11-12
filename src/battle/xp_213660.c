#include "m2c_macros.h"

void *BtlChar_GetPos(s32);                          /* extern */
f32 BtlUtil_WrapAngle(f32);                         /* extern */
f32 cosf(f32);                                      /* extern */
s32 func_00211310(s32, s32, s32);                /* extern */
M2C_UNK func_002113C0(s32, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */

void func_00213660(s32 arg0) {
    f32 temp_f20;
    f32 temp_f21;
    void *temp_s0;

    if (func_00211310(arg0, 2, 0x100) != 0) {
        temp_f21 = M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0x94);
        temp_f20 = BtlUtil_WrapAngle(temp_f21 + M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0x14));
        M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0x14) = temp_f20;
        M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xB4) = temp_f20;
        temp_s0 = BtlChar_GetPos(arg0);
        M2C_FIELD(temp_s0, f32 *, 0xB0) = (f32) (M2C_FIELD(temp_s0, f32 *, 0xB0) * cosf(temp_f21));
        func_002113C0(arg0, 2, 0x100, 0);
    }
}
