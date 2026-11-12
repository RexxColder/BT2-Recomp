#include "m2c_macros.h"

M2C_UNK Rand_Range();                      /* extern */
s32 func_002B8280();                                /* extern */
s32 func_002B9408();                             /* extern */
M2C_UNK func_002B9430();          /* extern */
M2C_UNK func_002D6108();                 /* extern */
extern M2C_UNK D_00379960 __attribute__((section(".data")));
extern M2C_UNK D_00379990 __attribute__((section(".data")));

void func_002BA790(s32 arg0, s32 *arg1) {
    s32 sp[40];
    s32 temp_s0;

    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00379960);
        return;
    }
    if (*arg1 == 0) {
        Rand_Range(&D_00379990);
        return;
    }
    temp_s0 = func_002B9408(arg0);
    func_002B9430(arg0, arg1, sp);
    func_002D6108(temp_s0, sp);
}
