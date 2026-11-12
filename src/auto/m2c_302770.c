#include "m2c_macros.h"

extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));

void func_00302770(void *arg0) {
    if ((D_0035D228 != 1) || (D_0035D220 > 0)) {
        M2C_FIELD(arg0, u8 *, 0x56) = (u8) M2C_FIELD(arg0, u8 *, 1);
    }
}
