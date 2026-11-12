#include "common.h"

s32 func_001F97A8(s32 arg0);

// Returns (word at +0x78 of arg0->+0x1530->+0x958) / 30 plus func_001F97A8(arg0).
s32 func_0023FA70(s32 arg0) {
    s32 obj = *(s32 *)((u8 *)arg0 + 0x1530);
    s32 base = *(s32 *)((u8 *)obj + 0x958);
    s32 q = *(s32 *)((u8 *)base + 0x78) / 30;
    return q + func_001F97A8(arg0);
}
