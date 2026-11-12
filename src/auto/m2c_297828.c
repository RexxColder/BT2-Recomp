#include "m2c_macros.h"

M2C_UNK func_002974F8(M2C_UNK, M2C_UNK *);          /* extern */
extern M2C_UNK D_003B0E00 __attribute__((section(".data")));

void func_00297828(s32 arg0, s32 arg1) {
    M2C_FIELD(&D_003B0E00, s32 *, 0) = arg0;
    M2C_FIELD(&D_003B0E00, s32 *, 0xC) = arg1;
    func_002974F8(0x50, &D_003B0E00);
}
