#include "m2c_macros.h"

M2C_UNK func_002EAEC0();                            /* extern */
M2C_UNK func_002EC198(s32);                         /* extern */
s32 func_002EC9C8(s32);                             /* extern */
extern s32 D_00367408 __attribute__((section(".data")));
extern s32 D_0036740C __attribute__((section(".data")));
extern s32 D_00367410 __attribute__((section(".data")));

void func_002EAF28(void) {
    if ((D_00367408 != 0) && (D_0036740C >= 0)) {
        if (func_002EC9C8(D_00367408) != 1) {
            func_002EC198(D_00367408);
        }
        D_00367410 = 1;
        func_002EAEC0();
    }
}
