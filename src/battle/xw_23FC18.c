#include "common.h"

// Returns 30000 divided by (s32)(f * 30.0f), f = float at +0x94 of arg0->+0x1530->+0x958.
s32 func_0023FC18(s32 arg0) {
    s32 base = *(s32 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x1530)) + 0x958);
    f32 f = *(f32 *)((u8 *)base + 0x94);
    s32 d = (s32)(f * 30.0f);
    return 30000 / d;
}
