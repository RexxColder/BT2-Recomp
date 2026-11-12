#include "m2c_macros.h"

M2C_UNK func_002EB648();             /* extern */
M2C_UNK func_00325830(); /* extern */
extern M2C_UNK D_0037C6A8 __attribute__((section(".data")));

void func_002F3738(s32 arg0, s32 arg1, M2C_UNK arg2) {
    s32 sp[8];
    func_00325830(sp, &D_0037C6A8, arg0, (u32) (arg1 + 0x7FF) >> 0xB);
    func_002EB648(sp, arg2);
}
