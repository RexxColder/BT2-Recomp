#include "m2c_macros.h"

extern void *D_00421CF4 __attribute__((section(".data")));

s32 func_003C2840(void) {
    s32 n;
    s32 q;
    s32 r;
    s32 w;

    n = M2C_FIELD(D_00421CF4, s32 *, 0x1D0);
    q = n / 16;
    if (q < 2) {
        r = n - q * 16;
        w = r / 4;
        return 24 * r + 12 * w;
    }
    return 24 * (q % 4) + 0xA0;
}
