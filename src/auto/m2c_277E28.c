#include "m2c_macros.h"

M2C_UNK func_001014E8(M2C_UNK);                     /* extern */
M2C_UNK func_00101560();                            /* extern */
extern s32 D_00388D84 __attribute__((section(".data")));

void func_00277E28(void) {
    D_00388D84 = 0;
    func_001014E8(-0x3C0);
    func_00101560();
}
