#include "m2c_macros.h"

s32 BtlChar_GetPos();                         /* extern */
M2C_UNK Quat_ToEuler();                     /* extern */
s32 func_00269A40();                    /* extern */
M2C_UNK func_00312650();               /* extern */
M2C_UNK func_003126C8();                    /* extern */

void func_002115D0(void *arg0) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;

    temp_s0 = BtlChar_GetPos(arg0);
    func_00312650(temp_s0, M2C_FIELD(arg0, s32 *, 0x1530) + 0x9C0, BtlChar_GetPos(arg0) + 0x60);
    func_003126C8(BtlChar_GetPos(arg0) + 0x10, M2C_FIELD(arg0, s32 *, 0x1530) + 0x9B0);
    temp_s0_2 = func_00269A40(M2C_FIELD(arg0, s32 *, 0x1530), 0);
    func_003126C8(BtlChar_GetPos(arg0) + 0x70, temp_s0_2 + 0x80);
    func_003126C8(BtlChar_GetPos(arg0) + 0x80, temp_s0_2 + 0x90);
    temp_s0_3 = BtlChar_GetPos(arg0) + 0x90;
    Quat_ToEuler(temp_s0_3, BtlChar_GetPos(arg0) + 0x80);
}
