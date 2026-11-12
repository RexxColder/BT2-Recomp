#include "m2c_macros.h"

void *memset(void *, int, unsigned int);
extern u8 *D_003876A4;

// Clears the sub-blocks of the object at D_003876A4 (when it exists) and resets the five per-slot words at +0x390 and the flag words at +0x3A4.
void func_00102360(void) {
    s32 var_a2;
    s32 temp_a0;

    if (D_003876A4 != NULL) {
        *(s32 *) (D_003876A4 + 0x28) = 0;
        memset(D_003876A4 + 0x2C, 0, 0x14);
        memset(D_003876A4 + 0x40, 0, 0x48);
        memset(D_003876A4 + 0x88, 0, 0x308);
        memset(D_003876A4 + 0x390, 0, 0xE8);
        memset(D_003876A4 + 0x478, 0, 0x14);
        memset(D_003876A4 + 0x48C, 0, 0x28);
        memset(D_003876A4 + 0x4B4, 0, 0xC);
        *(s32 *) (D_003876A4 + 0x4C0) = 0;
        *(s32 *) (D_003876A4 + 0x4C4) = 0;
        var_a2 = 0;
        do {
            temp_a0 = var_a2 * 4;
            var_a2 += 1;
            *(s32 *) ((s32) temp_a0 + (s32) D_003876A4 + 0x390) = 0;
            *(s32 *) ((s32) temp_a0 + (s32) D_003876A4 + 0x3A4) = 1;
        } while (var_a2 < 5);
    }
}
