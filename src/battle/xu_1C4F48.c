#include "common.h"

s32 func_001C4E08(s32 arg0);
s32 func_00129C28(s32 arg0, s32 arg1);

/* Takes an entry from func_001C4E08(arg0); if there is one, sets bit 0 of its first word, links it to the source at
   +4 of arg0 (or to arg1) through func_00129C28 at +0x10, sets the byte at +5 and returns 1. Returns 0 when none. */
s32 func_001C4F48(s32 arg0, s32 arg1) {
    s32 r = func_001C4E08(arg0);

    if (r != 0) {
        s32 p;

        *(s32 *)r |= 1;
        p = *(s32 *)(arg0 + 4);
        if (p != 0) {
            func_00129C28(r + 0x10, p + 0x10);
        } else {
            func_00129C28(r + 0x10, arg1 + 0x10);
        }
        *(u8 *)(r + 5) = 1;
        return 1;
    }
    return r;
}
