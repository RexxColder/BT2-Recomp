#include "m2c_macros.h"

M2C_UNK func_00129C28(M2C_UNK, s32, void *, M2C_UNK); /* extern */
extern M2C_UNK EftTrail_Update __attribute__((section(".data")));

void EftTrail_GetPos(void *arg0, M2C_UNK arg1) {
    if (arg0 != NULL) {
        if (*M2C_FIELD(arg0, s32 **, 0x28) == (void *)0x001A68A8u) { /* PS2 address of EftTrail_Update */
            func_00129C28(arg1, M2C_FIELD(arg0, s32 *, 0x38) + 0x40, arg0, arg1);
        }
    }
}
