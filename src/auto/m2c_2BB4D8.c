#include "m2c_macros.h"

M2C_UNK func_002BADC8();                 /* extern */
M2C_UNK func_00325830(); /* extern */
extern M2C_UNK D_00379E10 __attribute__((section(".data")));

void func_002BB4D8(s32 arg0, M2C_UNK arg1, s32 arg2) {
    s32 sp[8];
    func_00325830(sp, &D_00379E10, arg1, (u32) (arg2 + 0x7FF) >> 0xB);
    func_002BADC8(arg0, sp);
}
