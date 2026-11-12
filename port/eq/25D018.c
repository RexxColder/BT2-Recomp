#include "common.h"

extern u8 *D_00387A40;

u8 *func_0025D018(void) {
    u8 *temp;
    s32 n;

    temp = *(u8 **)(D_00387A40 + 0x38010);
    if (temp != NULL) {
        *(u8 **)(D_00387A40 + 0x38010) = *(u8 **)(temp + 0xDC);
        return temp;
    }
    if (*(s32 *)(D_00387A40 + 0x38014) < 0x3FF) {
        n = *(s32 *)(D_00387A40 + 0x38014);
        *(s32 *)(D_00387A40 + 0x38014) = n + 1;
        return D_00387A40 + n * 0xE0 + 0x10;
    }
    return NULL;
}
