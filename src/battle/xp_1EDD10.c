#include "m2c_macros.h"

M2C_UNK func_003126C8(s32, s32);                    /* extern */
extern void *D_00387A40;

void func_001EDD10(s32 arg0, s32 arg1) {
    s32 temp_a2;

    temp_a2 = arg0 * 0x1520;
    func_003126C8(M2C_FIELD(D_00387A40, s32 *, 8) + temp_a2 + 0x9B0, arg1);
}
