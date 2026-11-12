#include "common.h"

extern u8 *D_00387A30 __attribute__((section(".data")));

void DemoCam_SetTime(f32 arg0) {
    f32 temp_f0;

    if (*(s32 *)(D_00387A30 + 0x2B0) != 0) {
        temp_f0 = *(f32 *)(D_00387A30 + 0x2E0);
        if (temp_f0 <= arg0) {
            *(f32 *)(D_00387A30 + 0x2E4) = temp_f0;
        } else {
            *(f32 *)(D_00387A30 + 0x2E4) = arg0;
        }
        *(f32 *)(D_00387A30 + 0x2E0) = arg0;
    }
}
