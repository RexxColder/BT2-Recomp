#include "m2c_macros.h"

M2C_UNK Mtx_InverseRT(s32, s32);                    /* extern */
M2C_UNK func_00128900(s32);                         /* extern */
extern void *D_00387A40;

void func_001EDD40(s32 arg0) {
    s32 temp_s1;
    void *temp_s0;

    temp_s0 = M2C_FIELD(D_00387A40, s32 *, 8) + (arg0 * 0x1520);
    temp_s1 = temp_s0 + 0xA00;
    func_00128900(temp_s1);
    Mtx_InverseRT(temp_s0 + 0xA40, temp_s1);
    M2C_FIELD(temp_s0, s8 *, 0xAEC) = 0;
}
