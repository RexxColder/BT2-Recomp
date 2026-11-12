#include "m2c_macros.h"

M2C_UNK func_003126C8();                /* extern */
extern void *D_00387A40;

// For the battle slot in field 0x142C (if index valid), calls func_003126C8 on two sub-structs (+0x9A0 and +0x9B0, arg2).
void func_002070D8(void *arg0, s32 unused1, s32 arg2) {
    s32 temp_s0;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x142C);
    if (temp_v1 >= 0) {
        if (temp_v1 < M2C_FIELD(D_00387A40, s32 *, 0xC)) {
            temp_s0 = M2C_FIELD(D_00387A40, s32 *, 8) + (temp_v1 * 0x1520);
            func_003126C8(temp_s0 + 0x9A0, unused1);
            func_003126C8(temp_s0 + 0x9B0, arg2);
        }
    }
}
