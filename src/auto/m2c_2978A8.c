#include "m2c_macros.h"

M2C_UNK func_002974F8(M2C_UNK, M2C_UNK *);          /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern M2C_UNK D_003B0E00 __attribute__((section(".data")));
extern s32 gSndRpc;

void func_002978A8(void) {
    memset(gSndRpc + 0x68, 0, 0x100);
    func_002974F8(0x100, &D_003B0E00);
}
