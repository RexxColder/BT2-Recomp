#include "common.h"

s32 func_0028C648(u8 *arg0);
extern u8 D_003B0B00[] __attribute__((section(".data")));

/* 0x0010AC08: 0 if func_0028C648(a0) is nonzero; else n = *(s32 *)a0, and the result is 1 when one of
 * the n entries (0x180 bytes each, first at D_003B0B00 + 0x134) has bit 3 set in its first word, else 0. */
s32 func_0010AC08(u8 *arg0) {
    s32 n;
    s32 i;
    u8 *entry;

    if (func_0028C648(arg0) != 0) {
        return 0;
    }
    n = *(s32 *)arg0;
    if (n <= 0) {
        return 0;
    }
    entry = D_003B0B00 + 0x134;
    for (i = 0; i < n; i++) {
        if (*(s32 *)entry & 0x8) {
            return 1;
        }
        entry += 0x180;
    }
    return 0;
}
