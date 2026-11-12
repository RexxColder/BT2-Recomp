#include "m2c_macros.h"

M2C_UNK func_002FCDF0(s32);                         /* extern */
M2C_UNK func_002FD0D8();                            /* extern */
M2C_UNK func_00336EC8(s32);                         /* extern */
extern s32 D_003658EC __attribute__((section(".data")));
extern s32 D_003658F4 __attribute__((section(".data")));
extern s32 D_00365B80 __attribute__((section(".data")));

void func_00306C40(void) {
    s32 temp_v0;

    temp_v0 = D_003658EC - 1;
    D_003658EC = temp_v0;
    if (temp_v0 == 0) {
        func_002FCDF0(D_00365B80);
        D_00365B80 = 0;
        if (D_003658F4 != 0) {
            func_00336EC8(D_003658F4);
            D_003658F4 = 0;
        }
        func_002FD0D8();
    }
}
