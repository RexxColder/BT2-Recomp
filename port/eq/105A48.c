#include "common.h"

extern u8 *D_003876A0;
extern s32 *D_003876B4;

/* 0x00105A48: -1 when bit 45 (0x8000 << 45) of the s64 at +0x4D8 of D_003876A0 is set, else the word *D_003876B4. */
s32 func_00105A48(void) {
    s32 result = -1;

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & ((s64)0x8000 << 45))) {
        result = *D_003876B4;
    }
    return result;
}
