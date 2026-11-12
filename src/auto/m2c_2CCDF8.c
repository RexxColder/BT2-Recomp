#include "m2c_macros.h"

M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK);            /* extern */
extern s32 D_0037A4F0 __attribute__((section(".data")));

void func_002CCDF8(void) {
    if (D_0037A4F0 != 0x5A5A5A5A) {
        func_002C2FF0(0, 0xFF000201);
    }
}
