#include "common.h"

s32 func_00123300(s32 arg0, f32 fparg0) {
    u8 *base = (u8 *)arg0;
    s32 count = *(s32 *)(base + 0x18C);
    s32 start;
    s32 i;
    s32 t0;
    u8 *p;
    u8 v;

    if (count <= 0) {
        return *(s32 *)(base + 0x188) + count;
    }
    start = *(s32 *)(base + 0x188);
    p = base + start + 0x99C;
    v = *p;
    i = 0;
    for (;;) {
        p++;
        t0 = start + i;
        i++;
        if (fparg0 < *(f32 *)(base + 0x170 + v * 8 + 0x30)) {
            return t0;
        }
        if (i >= count) {
            break;
        }
        v = *p;
    }
    return start + count;
}
