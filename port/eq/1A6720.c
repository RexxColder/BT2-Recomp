#include "m2c_macros.h"

s32 func_00129C28(s32 arg0, s32 arg1);
extern M2C_UNK EftTrail_Update __attribute__((section(".data")));

void EftTrail_SetPos(void *arg0, s32 arg1) {
    if (arg0 != NULL && *(void **)*(u8 **)((u8 *)arg0 + 0x28) == (void *)0x001A68A8u) { /* PS2 address of EftTrail_Update */
        func_00129C28((s32)(*(u8 **)((u8 *)arg0 + 0x38) + 0x40), arg1);
    }
}
