#include "m2c_macros.h"

extern void *D_3876A4 __attribute__((section(".data")));
extern void *D_00421CF4 __attribute__((section(".data")));

void func_003C2D80(void) {
    s32 k;
    s32 j;

    for (k = 0; k < 2; k++) {
        for (j = 0; j < 5; j++) {
            s32 off = ((5 * k) << 2) + (4 * j);
            u8 *a2 = (u8 *)D_3876A4 + off;

            if (M2C_FIELD(a2, s32 *, 0x390) == (M2C_FIELD(D_00421CF4, s32 *, 0x1BC) + 0x4A)) {
                M2C_FIELD(a2, s32 *, 0x408) = 0;
            }
        }
    }
}
