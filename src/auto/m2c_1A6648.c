#include "m2c_macros.h"

extern M2C_UNK EftTrail_Update __attribute__((section(".data")));

void EftTrail_End(void *arg0, s32 arg1) {
    void *temp_v1;

    if ((arg0 != NULL) && (*M2C_FIELD(arg0, s32 **, 0x28) == (void *)0x001A68A8u)) { /* PS2 address of EftTrail_Update */
        temp_v1 = M2C_FIELD(arg0, void **, 0x38);
        M2C_FIELD(temp_v1, s32 *, 0x2C) = arg1;
        M2C_FIELD(temp_v1, s32 *, 0x28) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x28) | 1);
    }
}
