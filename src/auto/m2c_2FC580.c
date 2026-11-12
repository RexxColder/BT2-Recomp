#include "m2c_macros.h"

M2C_UNK func_00331710(M2C_UNK *);                   /* extern */
extern s32 D_003553A8 __attribute__((section(".data")));
extern M2C_UNK D_0037E068 __attribute__((section(".data")));

void func_002FC580(s32 arg0) {
    D_003553A8 = arg0;
    if (arg0 == 1) {
        func_00331710(&D_0037E068);
    }
}
