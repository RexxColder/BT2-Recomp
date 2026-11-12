#include "m2c_macros.h"

void func_002FD150(M2C_UNK, s32 *, M2C_UNK, M2C_UNK, M2C_UNK); /* extern */
extern s32 D_0039FEC0 __attribute__((section(".data")));

void func_00306658(s32 arg0) {
    D_0039FEC0 = arg0;
    func_002FD150(0x25, &D_0039FEC0, 1, 0, 0);
}
