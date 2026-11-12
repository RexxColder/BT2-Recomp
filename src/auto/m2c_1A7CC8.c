#include "m2c_macros.h"

M2C_UNK func_00129C28(s32, s32, void *);            /* extern */
extern M2C_UNK EftStruggle_Update __attribute__((section(".data")));
extern void **gEftStruggle;

void EftStruggle_SetPos(s32 arg0) {
    void *temp_a2;

    if (gEftStruggle != NULL) {
        temp_a2 = M2C_FIELD(*gEftStruggle, void **, 4);
        if ((temp_a2 != NULL) && !(M2C_FIELD(temp_a2, u8 *, 0) & 1 & 0xFF) && (*M2C_FIELD(temp_a2, s32 **, 0x28) == (void *)0x001A7FA0u)) { /* PS2 address of EftStruggle_Update */
            func_00129C28(M2C_FIELD(temp_a2, s32 *, 0x38), arg0, temp_a2);
        }
    }
}
