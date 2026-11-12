#include "common.h"

s32 func_002BFF40(u8 *arg0) {
    s32 v = -1;

    if (*(s32 *)(arg0 + 4) != 0) {
        v = 0;
        if (*(s32 *)(arg0 + 0) == 0) {
            v = -1;
            if (*(s32 *)(arg0 + 8) != 0 && *(s32 *)(arg0 + 0xC) > 0 && *(s32 *)(arg0 + 0x14) <= 0) {
                v = 0;
            }
        }
    }
    return v;
}
