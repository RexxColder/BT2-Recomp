#include "common.h"

s32 func_002C54C8(s32 arg0);

s32 func_002C26C0(u8 *arg0) {
    s32 r;

    if (*(s32 *)(arg0 + 0x36B0) == 0) {
        return 0;
    }
    r = func_002C54C8((s32)arg0);
    if (r <= 0) {
        return *(s32 *)(arg0 + 0x36B0) + 0xC;
    }
    return 0;
}
