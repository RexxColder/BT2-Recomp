#include "common.h"

s32 func_0020A658(s32 a0);
extern u8 *D_003876A0;

/* 0x001264F0: nonzero if func_0020A658(a0) or flag 0x100 of the state at +0x4D8. */
s32 BtlScene_IsCharStopped(s32 a0) {
    s32 r = func_0020A658(a0) != 0;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        r = 1;
    }
    return r;
}
