#include "m2c_macros.h"

M2C_UNK func_0026EB78(void *, M2C_UNK *);           /* extern */
extern void *D_00387978;
extern M2C_UNK D_00387980 __attribute__((section(".data")));

void func_00248690(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_00387978, s32 *, 0x38);
    if (!(temp_v0 & 8)) {
        M2C_FIELD(D_00387978, s32 *, 0x38) = (s32) (temp_v0 | 8);
        M2C_FIELD(D_00387978, s32 *, 0x38) = (s32) (M2C_FIELD(D_00387978, s32 *, 0x38) & ~4);
        func_0026EB78(D_00387978 + 4, &D_00387980);
    }
}
