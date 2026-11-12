#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);

void func_002E33B8(void *arg0, void *arg1, s32 arg2) {
    u8 *blk = (u8 *)arg0 + 0x14C;
    s32 cur = *(s32 *)(blk + 8);
    s32 rem = *(s32 *)(blk + 4) - cur;
    s32 n = (arg2 < rem) ? arg2 : rem;

    *(s32 *)(blk + 8) = cur + n;
    memcpy(*(u8 **)blk + cur, arg1, n);
}
