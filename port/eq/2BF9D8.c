#include "common.h"

void func_002BF9D8(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 i;
    s32 v = arg2;

    for (i = 0; i < 8; i++) {
        s32 src = *(s32 *)(arg1 + i * 4);

        *(s32 *)(arg0 + i * 4) = v;
        v += src;
    }
}
