#include "m2c_macros.h"

M2C_UNK func_00307798();                            /* extern */
extern s32 D_00348C50 __attribute__((section(".data")));
extern s32 D_00348C54 __attribute__((section(".data")));

void func_002EA028(s32 arg0, s32 arg1) {
    D_00348C50 = arg0;
    D_00348C54 = arg1;
    func_00307798(arg0, arg1);
}
