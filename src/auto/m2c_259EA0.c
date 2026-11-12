#include "m2c_macros.h"

M2C_UNK func_0026EA88(void *);                      /* extern */
M2C_UNK func_0026EAE0(void *, M2C_UNK);             /* extern */
extern void *D_00387A10;

void func_00259EA0(s32 arg0, s32 arg1) {
    M2C_FIELD(D_00387A10, s32 *, 0xB0) = arg0;
    M2C_FIELD(D_00387A10, s32 *, 0xB4) = arg1;
    func_0026EAE0(D_00387A10 + 0x2C, 0x1E);
    func_0026EA88(D_00387A10 + 0x2C);
}
