#include "common.h"

extern u8 *D_003877D0;

/* 0x00195220: record arg0 of 0x50 bytes at D_003877D0: word +4 when word +8 is non-zero, else -1. */
s32 func_00195220(s32 arg0) {
    u8 *rec = D_003877D0 + arg0 * 0x50;

    if (*(s32 *)(rec + 8) == 0) {
        return -1;
    }
    return *(s32 *)(rec + 4);
}
