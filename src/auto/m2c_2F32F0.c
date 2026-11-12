#include "m2c_macros.h"

M2C_UNK func_002F2718(void *);                      /* extern */
s32 func_002F33A8(s32 *);                           /* extern */
extern s32 D_00353F84 __attribute__((section(".data")));

void func_002F32F0(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x50) != 0) && (M2C_FIELD(arg0, s32 *, 8) == 0)) {
        M2C_FIELD(arg0, s8 *, 0x45) = 1;
        do {
            if (func_002F33A8(&D_00353F84) == 1) {
                func_002F2718(arg0);
                D_00353F84 = 0;
            }
        } while (M2C_FIELD(arg0, s8 *, 0x45) != 0);
    }
}
