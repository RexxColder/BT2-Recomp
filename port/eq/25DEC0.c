#include "common.h"

void func_0025DEC0(u8 *arg0, s32 arg1) {
    s32 *p;
    s32 v;

    *(s32 *)(arg0 + 0xAF0) = 0x1E;
    if (arg1 == 1) {
        *(s32 *)(arg0 + 0xAF0) = 0x2000001E;
    }
    p = *(s32 **)(arg0 + 0x44);
    v = 0x20000;
    if (!(*p & 0x1000000)) {
        v = 0x10000;
    }
    *(s32 *)(arg0 + 0xAF0) = *(s32 *)(arg0 + 0xAF0) | v;
}
