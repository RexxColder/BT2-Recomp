#include "common.h"

extern u8 EftTrail_Update[] __attribute__((section(".data")));

void EftTrail_SetWidth(void *arg0, f32 farg0) {
    u8 *temp_v0;
    s32 *temp_a0;

    if (arg0 != NULL) {
        temp_a0 = *(s32 **)((u8 *)arg0 + 0x28);
        if (*temp_a0 == (s32)0x001A68A8u) { /* PS2 address of EftTrail_Update */
            temp_v0 = *(u8 **)((u8 *)arg0 + 0x38);
            *(f32 *)(temp_v0 + 0x20) = farg0;
            *(f32 *)(temp_v0 + 0x1C) = farg0;
        }
    }
}
