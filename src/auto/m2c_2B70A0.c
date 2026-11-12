#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B3190(void *);                      /* extern */
M2C_UNK func_002B6D10(void *);                      /* extern */
M2C_UNK func_002B7138(void *);                      /* extern */
s32 func_002B8280();                                /* extern */
M2C_UNK func_002BD380(M2C_UNK);                     /* extern */
extern M2C_UNK D_00378C48 __attribute__((section(".data")));

void func_002B70A0(void *arg0, s32 arg1) {
    if (func_002B8280(arg0) != 1) {
        Rand_Range(&D_00378C48);
        return;
    }
    func_002BD380(1);
    func_002B7138(arg0);
    M2C_FIELD(arg0, s32 *, 0x1BC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x1D4) = 0;
    M2C_FIELD(arg0, s32 *, 0x1D0) = 2;
    M2C_FIELD(arg0, s32 *, 0x1D8) = 0;
    M2C_FIELD(arg0, s32 *, 0x1DC) = 0;
    func_002B6D10(arg0);
    func_002BD380(0);
    func_002B3190(arg0);
}
