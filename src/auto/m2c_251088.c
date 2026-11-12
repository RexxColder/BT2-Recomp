#include "m2c_macros.h"

M2C_UNK func_0026EB78(void *, M2C_UNK *);           /* extern */
extern void *D_003879B0;
extern M2C_UNK D_003879B8 __attribute__((section(".data")));

void func_00251088(void) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(D_003879B0, s32 *, 0x6C);
    if (!(temp_v0 & 8)) {
        M2C_FIELD(D_003879B0, s32 *, 0x6C) = (s32) (temp_v0 | 8);
        M2C_FIELD(D_003879B0, s32 *, 0x6C) = (s32) (M2C_FIELD(D_003879B0, s32 *, 0x6C) & ~4);
        func_0026EB78(D_003879B0 + 0x1C, &D_003879B8);
    }
}
