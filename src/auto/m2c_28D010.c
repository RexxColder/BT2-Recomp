#include "m2c_macros.h"

void ColBox_AddPointKeepW(void *arg0, void *arg1) {
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;

    temp_f1 = M2C_FIELD(arg1, f32 *, 0);
    if (temp_f1 < M2C_FIELD(arg0, f32 *, 0)) {
        M2C_FIELD(arg0, f32 *, 0) = temp_f1;
    }
    if (M2C_FIELD(arg0, f32 *, 0xC) < M2C_FIELD(arg1, f32 *, 0)) {
        M2C_FIELD(arg0, f32 *, 0xC) = M2C_FIELD(arg1, f32 *, 0);
    }
    temp_f1_2 = M2C_FIELD(arg1, f32 *, 4);
    if (temp_f1_2 < M2C_FIELD(arg0, f32 *, 4)) {
        M2C_FIELD(arg0, f32 *, 4) = temp_f1_2;
    }
    if (M2C_FIELD(arg0, f32 *, 0x10) < M2C_FIELD(arg1, f32 *, 4)) {
        M2C_FIELD(arg0, f32 *, 0x10) = M2C_FIELD(arg1, f32 *, 4);
    }
    temp_f1_3 = M2C_FIELD(arg1, f32 *, 8);
    if (temp_f1_3 < M2C_FIELD(arg0, f32 *, 8)) {
        M2C_FIELD(arg0, f32 *, 8) = temp_f1_3;
    }
    if (M2C_FIELD(arg0, f32 *, 0x14) < M2C_FIELD(arg1, f32 *, 8)) {
        M2C_FIELD(arg0, f32 *, 0x14) = M2C_FIELD(arg1, f32 *, 8);
    }
}
