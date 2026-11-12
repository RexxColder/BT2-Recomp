#include "m2c_macros.h"

extern M2C_UNK EftStruggle_Update __attribute__((section(".data")));
extern void **gEftStruggle;

void EftStruggle_SetBias(f32 arg0) {
    void *temp_a1;
    void *temp_v0;

    if (gEftStruggle != NULL) {
        temp_a1 = M2C_FIELD(*gEftStruggle, void **, 4);
        if ((temp_a1 != NULL) && !(M2C_FIELD(temp_a1, u8 *, 0) & 1 & 0xFF) && (*M2C_FIELD(temp_a1, s32 **, 0x28) == (void *)0x001A7FA0u)) { /* PS2 address of EftStruggle_Update */
            temp_v0 = M2C_FIELD(temp_a1, void **, 0x38);
            M2C_FIELD(temp_v0, f32 *, 0x20) = arg0;
            if (arg0 > 1.0f) {
                M2C_FIELD(temp_v0, f32 *, 0x20) = 1.0f;
            }
            if (M2C_FIELD(temp_v0, f32 *, 0x20) < 0.0f) {
                M2C_FIELD(temp_v0, f32 *, 0x20) = 0.0f;
            }
        }
    }
}
