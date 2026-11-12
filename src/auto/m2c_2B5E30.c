#include "m2c_macros.h"

M2C_UNK func_002D04A8(s32, M2C_UNK, M2C_UNK *);     /* extern */
extern M2C_UNK func_002B5E80 __attribute__((section(".data")));

void func_002B5E30(M2C_UNK *arg0) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 0x3C);
    func_002D04A8(temp_s1, 0x4B, &func_002B5E80);
    func_002D04A8(temp_s1, 0x4C, arg0);
}
