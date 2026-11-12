#include "common.h"

extern u8 *D_00387A30;

s32 DemoCam_IsInUse(void) {
    s32 result = 1;
    if (*(s32 *)(D_00387A30 + 0x2B0) == 0) {
        result = *(u8 *)(D_00387A30 + 0x31C) != 0;
    }
    return result;
}
