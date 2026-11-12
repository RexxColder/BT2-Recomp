#include "m2c_macros.h"

extern M2C_UNK EftStruggle_Update __attribute__((section(".data")));
extern void **gEftStruggle;

f32 EftStruggle_GetBias(void) {
    f32 var_f0;
    void *temp_a1;

    var_f0 = 0.0f;
    if (gEftStruggle != NULL) {
        temp_a1 = M2C_FIELD(*gEftStruggle, void **, 4);
        if ((temp_a1 != NULL) && !(M2C_FIELD(temp_a1, u8 *, 0) & 1 & 0xFF) && (*M2C_FIELD(temp_a1, s32 **, 0x28) == (void *)0x001A7FA0u)) { /* PS2 address of EftStruggle_Update */
            var_f0 = M2C_FIELD(M2C_FIELD(temp_a1, void **, 0x38), f32 *, 0x20);
        }
    }
    return var_f0;
}
