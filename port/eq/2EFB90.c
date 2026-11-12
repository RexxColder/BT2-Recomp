#include "common.h"

u32 func_002EFB90(u8 *arg0, s32 arg1) {
    u8 *slot = *(u8 **)(arg0 + 0xC) + arg1 * 4;
    u8 *obj = *(u8 **)(slot + 0x8);
    u8 *t = *(u8 **)(obj + 0x8);
    u8 *vt = *(u8 **)t;
    u32 (*fn)(u8 *, s32, u8 *) = (u32 (*)(u8 *, s32, u8 *))(*(s32 *)(vt + 0x24));

    return fn(t, 0, vt) >> 1;
}
