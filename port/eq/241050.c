#include "common.h"

u8 *func_00208768(s32 arg0, s32 arg1);

s32 func_00241050(u8 *arg0, s32 arg1) {
    u8 *t = func_00208768(*(s32 *)(arg0 + 0x1534), arg1);
    s32 v = 1;

    if (t != NULL) {
        s32 x = *(s32 *)(t + 0x14);

        v = (x > 0) ? x : 1;
    }
    return v;
}
