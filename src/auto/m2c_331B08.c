#include "m2c_macros.h"

M2C_UNK func_0032E990(M2C_UNK, s32);                /* extern */
M2C_UNK func_0032F810(M2C_UNK);                     /* extern */
extern s32 D_0036AA8C __attribute__((section(".data")));
extern s32 D_003A9594 __attribute__((section(".data")));

void sceSifExitCmd(void) {
    func_0032F810(5);
    func_0032E990(5, D_003A9594);
    D_0036AA8C = 0;
}
