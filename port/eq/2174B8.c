#include "common.h"

s32 func_002174B8(u8 *arg0) {
    s32 v1;

    v1 = *(s32 *)(arg0 + 0xC0C);
    if (v1 != -1) {
        return v1;
    }
    return *(s32 *)(arg0 + 0xC08);
}
