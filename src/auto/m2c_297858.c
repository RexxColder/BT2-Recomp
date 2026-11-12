#include "m2c_macros.h"

M2C_UNK func_002974F8(M2C_UNK, s32 *);              /* extern */
extern s32 D_003B0E00 __attribute__((section(".data")));

void func_00297858(s32 arg0) {
    D_003B0E00 = arg0;
    func_002974F8(0x60, &D_003B0E00);
}
