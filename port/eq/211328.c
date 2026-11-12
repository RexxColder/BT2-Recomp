#include "common.h"

/* 0x00211328: p = arg0 + 4 * arg1; the word at p + 0x378 when (word at p + 0x2F4) & arg2 is set, else the word at
 * p + 0x440; returns 1 when that word has any bit of arg2. */
s32 func_00211328(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = arg0 + arg1 * 4;
    s32 v;

    if (*(s32 *)(p + 0x2F4) & arg2) {
        v = *(s32 *)(p + 0x378);
    } else {
        v = *(s32 *)(p + 0x440);
    }
    return (v & arg2) != 0;
}
