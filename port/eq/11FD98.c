#include "common.h"

/* 0x0011FD98: base = arg0 + 0x38. If the words at base+0x108 and base+0x10C are equal, returns 1 when the byte at
 * arg0+0x158 is 0, else returns the word at base+4. Otherwise ANDs the word at base+4 with the words at
 * arg0+0xC0+4*i, for i running from the first index (base+0x108) and wrapping to 0 after 31, until the index
 * reaches the value at base+0x10C (the loop body runs at least once). */
s32 func_0011FD98(u8 *arg0) {
    u8 *base = arg0 + 0x38;
    s32 start = *(s32 *)(base + 0x108);
    s32 end = *(s32 *)(base + 0x10C);
    s32 x;
    s32 idx;
    s32 old;

    if (start == end) {
        if (*(u8 *)(arg0 + 0x158) == 0) {
            return 1;
        }
        return *(s32 *)(base + 4);
    }
    x = *(s32 *)(base + 4);
    idx = start;
    do {
        old = idx;
        idx = old + 1;
        if (idx >= 0x20) {
            idx = 0;
        }
        x &= *(s32 *)(arg0 + 0xC0 + old * 4);
    } while (idx != end);
    return x;
}
