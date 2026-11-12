#include "common.h"

s32 func_002F6B50(s32 arg0, s32 arg1, s32 arg2);

s32 func_002BE000(s32 arg0, s32 arg1, s32 *arg2) {
    s32 sp[4];
    s32 p;
    s32 off;

    p = arg0;
    off = 0;
    *arg2 = 0;
    while (off < arg1) {
        if (func_002F6B50(p, 0x12, (s32)sp) != 0) {
            *arg2 = 1;
            return off;
        }
        p += 0x12;
        off += 0x12;
    }
    return off;
}
