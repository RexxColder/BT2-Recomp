#include "common.h"

s32 func_001EBC80(u8 *arg0) {
    s32 v0 = 0;
    s16 idx = *(s16 *)(arg0 + 6);

    if (idx < *(s16 *)(arg0 + 4)) {
        u8 *base = *(u8 **)arg0;

        v0 = *(s32 *)(base + idx * 4);
        *(s16 *)(arg0 + 6) = (s16)(idx + 1);
    }
    return v0;
}
