#include "common.h"

s32 func_001A21C8(u8 *arg0) {
    u8 *p = arg0 + 0x78;
    s32 v1 = *(s32 *)p;
    s32 a = 0;

    for (;;) {
        p += 0x60;
        if (v1 & 1) {
            return 1;
        }
        a += 1;
        if (a >= 8) {
            return 0;
        }
        v1 = *(s32 *)p;
    }
}
