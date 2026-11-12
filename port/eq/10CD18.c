#include "common.h"

void func_0010CD18(s32 arg0) {
    s32 off;

    *(s32 *)(arg0 + 0x704) = 0;
    for (off = 0x690; off <= 0x700; off += 4) {
        *(s32 *)(arg0 + off) = 0;
    }
}
