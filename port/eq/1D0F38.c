#include "common.h"

extern s32 D_00387E9C;

s32 func_001D0F38(s32 arg0, s32 arg1) {
    s32 a3;
    s32 base;

    a3 = arg1 & 0xFF;
    if (*(u8 *) (D_00387E9C + 0x1491) == 0) {
        return 0;
    }
    base = *(s32 *) (D_00387E9C + 0x1400) + arg0 * 0x14;
    if (a3 == 0) {
        if (*(u8 *) (base + 8) != 3) {
            *(u8 *) (base + 8) = 3;
            *(s32 *) base = arg0;
            *(s32 *) (base + 4) = 0;
        }
        return 1;
    }
    if (a3 == 1) {
        if (*(u8 *) (base + 8) == 3) {
            *(u8 *) (base + 8) = 0;
            *(s32 *) (base + 4) = 0;
        }
        return 1;
    }
    return 1;
}
