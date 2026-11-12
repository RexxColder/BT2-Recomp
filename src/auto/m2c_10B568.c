#include "m2c_macros.h"

void *func_0010B078();                              /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003876A0;
extern M2C_UNK func_001125B0 __attribute__((section(".data")));

void func_0010B568(void) {
    void *temp_s0;

    temp_s0 = func_0010B078();
    if ((M2C_FIELD(D_003876A0, s32 *, 0xB8) != 6) && (M2C_FIELD(temp_s0, M2C_UNK **, 0x135C) == NULL)) {
        memset(temp_s0 + 0xF70, 0, 0x150);
        M2C_FIELD(temp_s0, M2C_UNK **, 0x135C) = &func_001125B0;
    }
}
