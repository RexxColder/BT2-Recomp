#include "common.h"

/* 0x0028C610: r = func_0028C520(a0, a1); return Pad_StickToFloat(r, a2) (tail call, f32 result in f0). */
s32 func_0028C520(s32 arg0, s32 arg1);
f32 Pad_StickToFloat(s32 arg0, s32 arg1);

f32 func_0028C610(s32 a0, s32 a1, s32 a2) {
    s32 r;

    r = func_0028C520(a0, a1);
    return Pad_StickToFloat(r, a2);
}
