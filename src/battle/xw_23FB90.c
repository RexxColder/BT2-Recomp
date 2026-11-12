#include "common.h"

s32 func_001F9848(s32 arg0);

// Returns (word at +0x8C of arg0->+0x1530->+0x958) / 30 plus func_001F9848(arg0).
s32 func_0023FB90(s32 arg0) {
    s32 obj = *(s32 *)((u8 *)arg0 + 0x1530);
    s32 base = *(s32 *)((u8 *)obj + 0x958);
    s32 q = *(s32 *)((u8 *)base + 0x8C) / 30;
    return q + func_001F9848(arg0);
}
