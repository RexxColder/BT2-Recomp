#include "m2c_macros.h"

extern void *D_00421CF4 __attribute__((section(".data")));

s32 func_003C2F58(s32 arg0) {
    s32 n = M2C_FIELD(D_00421CF4, s32 *, 0x684);
    u8 *base = M2C_FIELD(D_00421CF4, u8 **, 0x688);
    s32 i;

    for (i = 0; i < n; i++) {
        if (*(s32 *)(base + 8 + (i * 0x2C)) == arg0) {
            return 1;
        }
    }
    return 0;
}
