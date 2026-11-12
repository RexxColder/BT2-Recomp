#include "common.h"

s32 func_00299AE0(s32 arg0) {
    s32 a1 = arg0;
    s32 a2 = 1;

    if (arg0 <= 0) {
        return 0;
    }
    if (1 < arg0) {
        a2 = 2;
        for (;;) {
            a1 = a1 >> 1;
            if (!(a2 < a1)) {
                break;
            }
            a2 = a2 * 2;
        }
    }
    a1 = a2;
    for (;;) {
        s32 t = (arg0 / a1 + a1) >> 1;

        if (!(t < a1)) {
            return a1;
        }
        a1 = t;
    }
}
