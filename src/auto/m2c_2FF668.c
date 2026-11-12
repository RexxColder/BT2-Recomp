#include "m2c_macros.h"

M2C_UNK func_002FF578(void *, s32, s32, s32);       /* extern */
extern M2C_UNK D_00356E98 __attribute__((section(".data")));

void func_002FF668(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0) = 0;
    M2C_FIELD(arg1, s32 *, 4) = 0;
    if (M2C_FIELD(&D_00356E98, s32 *, 0) != 0) {
        func_002FF578(arg1, arg0, M2C_FIELD(&D_00356E98, s32 *, 0), M2C_FIELD(&D_00356E98, s32 *, 4));
    }
}
