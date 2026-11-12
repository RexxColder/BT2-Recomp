#include "m2c_macros.h"

M2C_UNK func_00303C00(M2C_UNK *, M2C_UNK *);        /* extern */
void *memset(void *, int, unsigned int);
extern M2C_UNK D_0037F580 __attribute__((section(".data")));
extern M2C_UNK D_0037F590 __attribute__((section(".data")));
extern M2C_UNK D_0037F5B0 __attribute__((section(".data")));
extern M2C_UNK D_0037F5C0 __attribute__((section(".data")));

void func_00303E88(void *arg0) {
    if (arg0 == NULL) {
        func_00303C00(&D_0037F580, &D_0037F590);
        return;
    }
    if (M2C_FIELD(arg0, s32 *, 4) == 0) {
        func_00303C00(&D_0037F5B0, &D_0037F5C0);
        return;
    }
    memset(arg0, 0, 0x24);
    M2C_FIELD(arg0, s32 *, 4) = 0;
}
