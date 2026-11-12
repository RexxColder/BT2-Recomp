#include "common.h"

s32 func_0020A6A0(void);
extern u8 *D_003876A0;

/* 0x00126528: same as BtlScene_IsCharStopped but with func_0020A6A0(). */
s32 func_00126528(void) {
    s32 r = func_0020A6A0() != 0;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        r = 1;
    }
    return r;
}
