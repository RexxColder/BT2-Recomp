#include "m2c_macros.h"

M2C_UNK func_002FDCF0(s32);                         /* extern */
M2C_UNK func_002FF980();                            /* extern */
extern s32 D_003534A0 __attribute__((section(".data")));

void func_002EF990(s32 arg0) {
    D_003534A0 = arg0;
    func_002FF980(arg0);
    func_002FDCF0(arg0);
}
