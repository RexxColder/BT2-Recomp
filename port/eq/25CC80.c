#include "common.h"

extern u8 *D_00387A40;

s32 func_0025CC80(s32 arg0) {
    u8 *p = D_00387A40 + 0x38184;
    s32 i = 0;

    for (;;) {
        s32 e = *(s32 *)p;
        s32 ret = i;

        p += 4;
        i++;
        if (e == arg0) {
            return ret;
        }
        if (i >= 0x20) {
            return 0;
        }
    }
}
