#include "m2c_macros.h"

void *func_0010B078();                              /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */
extern void *D_003876A0;
extern M2C_UNK func_00111138 __attribute__((section(".data")));

void func_0010B5D0(void) {
    void *temp_s0;

    temp_s0 = func_0010B078();
    if ((M2C_FIELD(D_003876A0, s32 *, 0xB8) != 6) && (M2C_FIELD(temp_s0, M2C_UNK **, 0x1360) == NULL)) {
        memset(temp_s0 + 0xD0, 0, 0xEA0);
        M2C_FIELD(temp_s0, M2C_UNK **, 0x1360) = &func_00111138;
    }
}
