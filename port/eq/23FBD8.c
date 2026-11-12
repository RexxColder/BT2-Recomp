#include "common.h"

s32 func_0023FBD8(u8 *arg0) {
    u8 *obj = *(u8 **)(arg0 + 0x1530);
    u8 *sub = *(u8 **)(obj + 0x958);
    f32 x = *(f32 *)(sub + 0x90) * 30.0f;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    s32 d = (s32)x;

    return 0x7530 / d;
}
