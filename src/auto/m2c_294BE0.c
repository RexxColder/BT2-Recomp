#include "m2c_macros.h"

M2C_UNK func_00312650(void *, void *, s32);              /* extern */
M2C_UNK func_003126C8(void *, void *);              /* extern */
M2C_UNK sceVu0Normalize(void *, void *);            /* extern */

void ColCapsule_GetLongSegDir(void *arg0, void *arg1, void *arg2) {
    void *temp_s4;

    temp_s4 = arg2 + 0x10;
    func_00312650(arg1, temp_s4, arg2);
    sceVu0Normalize(arg1, arg1);
    func_003126C8(arg0, arg2);
    func_003126C8(arg0 + 0x10, temp_s4);
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (M2C_FIELD(arg0, f32 *, 0x10) + (M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) + (M2C_FIELD(arg1, f32 *, 4) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg0, f32 *, 0x18) = (f32) (M2C_FIELD(arg0, f32 *, 0x18) + (M2C_FIELD(arg1, f32 *, 8) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg0, f32 *, 0) - (M2C_FIELD(arg1, f32 *, 0) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg0, f32 *, 4) = (f32) (M2C_FIELD(arg0, f32 *, 4) - (M2C_FIELD(arg1, f32 *, 4) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg0, f32 *, 8) = (f32) (M2C_FIELD(arg0, f32 *, 8) - (M2C_FIELD(arg1, f32 *, 8) * M2C_FIELD(arg2, f32 *, 0x20)));
    M2C_FIELD(arg1, f32 *, 0xC) = 1.0f;
}
