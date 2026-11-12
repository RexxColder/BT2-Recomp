#include "common.h"

/* 0x0021FE80 BtlActB_NextVariant: for arg1 >= 2, the counter at +0xB50 is advanced and reduced modulo arg1 (stored
 * back, and returned); for arg1 < 2 the result is 0 and nothing is stored. */
s32 BtlActB_NextVariant(u8 *arg0, s32 arg1) {
    s32 v = 0;
    s32 t;

    if (arg1 >= 2) {
        t = *(s32 *)(arg0 + 0xB50) + 1;
        *(s32 *)(arg0 + 0xB50) = t;
        v = t % arg1;
        *(s32 *)(arg0 + 0xB50) = v;
    }
    return v;
}
