#include "m2c_macros.h"

s32 func_003D6D18(u8 *arg0) {
    s32 n = M2C_FIELD(arg0, s32 *, 0x331C);
    s32 i;

    for (i = 0; i < n; i++) {
        u16 f = *(u16 *)(arg0 + 0x333C + (i * 0x20));

        if ((f & 1) && !(f & 2)) {
            return 0;
        }
    }
    return 1;
}
