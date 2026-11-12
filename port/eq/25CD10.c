#include "common.h"

extern u8 *D_00387A40;

s32 func_0025CD10(void) {
    s32 bit;
    s32 word;
    s32 i = 1;

    for (;;) {
        word = *(s32 *)(D_00387A40 + 0x38020);
        bit = 1 << i;
        if (word & bit) {
            i++;
            if (i >= 0x20) {
                return 0;
            }
            continue;
        }
        *(s32 *)(D_00387A40 + 0x38020) = word | bit;
        return i;
    }
}
