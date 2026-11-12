#include "common.h"

s32 func_002C2D60(u8 *arg0) {
    u8 *p = arg0 + 0x78;
    s32 v = 0;

    if (*(s32 *)(arg0 + 0x78) != 0) {
        v = *(s32 *)(p + 4) * 0x64 + *(s32 *)(p + 8);
    }
    return v;
}
