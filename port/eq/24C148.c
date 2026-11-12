#include "m2c_macros.h"

extern u8 *D_003876A4;
extern s32 D_00387F2C;

s32 func_0024C148(void) {
    u8 *p = D_003876A4;
    s32 off;

    if (*(s32 *)(p + 0x4C8) != 0 && *(s32 *)(p + 0x4CC) != 0) {
        off = (*(s32 *)(p + 0x48C) & 2) ? 0x4C4 : 0x4C0;
        return *(s32 *)(p + off + 8);
    }
    return D_00387F2C;
}
