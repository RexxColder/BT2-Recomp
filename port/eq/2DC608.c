#include "common.h"

u8 *func_002DC608(u8 *arg0, s32 arg1, s32 arg2) {
    s32 a3;
    u8 *p;

    a3 = 0;
    p = arg0;
    if (arg1 <= 3) {
        return NULL;
    }
    for (;;) {
        if (p[0] == 0 && p[1] == 0 && p[2] == 1 && p[3] == (arg2 & 0xFF)) {
            return p;
        }
        a3 += 1;
        p += 1;
        if (a3 + 3 >= arg1) {
            return NULL;
        }
    }
}
