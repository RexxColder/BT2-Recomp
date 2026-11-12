#include "common.h"

extern u8 *D_003876A0;

s32 func_002AE000(void) {
    s64 flag = *(s64 *)(D_003876A0 + 0x4D8);

    if ((flag & ((s64)0x8000 << 22)) == 0) {
        return 8;
    }
    return 1;
}
