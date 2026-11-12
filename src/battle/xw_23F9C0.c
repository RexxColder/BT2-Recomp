#include "common.h"

s32 func_001F9758(s32 arg0);

// Returns (word at +0x70 of arg0->+0x1530->+0x958) / 30 plus func_001F9758(arg0) plus the word at +0xAEC of arg0.
s32 func_0023F9C0(s32 arg0) {
    s32 obj = *(s32 *)((u8 *)arg0 + 0x1530);
    s32 base = *(s32 *)((u8 *)obj + 0x958);
    s32 q = *(s32 *)((u8 *)base + 0x70) / 30;
    s32 r = func_001F9758(arg0);
    s32 extra = *(s32 *)((u8 *)arg0 + 0xAEC);
    return q + r + extra;
}
