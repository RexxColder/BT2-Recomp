#include "common.h"

s32 func_00106D68(u8 *arg0) {
    s32 count;
    s32 k;
    s32 v;
    u8 *p;

    count = *(s32 *)(arg0 + 4);
    if (count <= 0) {
        return 0;
    }
    p = *(u8 **)arg0 + 8;
    v = *(s32 *)p;
    k = 0;
    for (;;) {
        p += 0x20;
        if (v != 0 && *(s32 *)(arg0 + 0x14) == k) {
            return 1;
        }
        k += 1;
        if (k >= count) {
            return 0;
        }
        v = *(s32 *)p;
    }
}
