#include "common.h"

s32 func_001A83D8(u8 *arg0) {
    u8 *a1 = *(u8 **)(arg0 + 0x38) + 0x374;
    s32 a2 = 0;
    s32 v1 = *(s32 *)a1;

    for (;;) {
        s32 idx = a2;

        a1 += 4;
        a2 += 1;
        if (v1 == 0) {
            return idx;
        }
        if (a2 >= 4) {
            return 0;
        }
        v1 = *(s32 *)a1;
    }
}
