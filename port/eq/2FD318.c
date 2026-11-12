#include "common.h"

/* 0x002FD318: func_002FC550(0x8000, a1); sceCdLayerSearchFile(a0, a1, D_0035600C); return func_002FC550(0x8001). */
extern s32 D_0035600C;
s32 func_002FC550(s32 arg0);
s32 sceCdLayerSearchFile(s32 arg0, s32 arg1, s32 arg2);

s32 func_002FD318(s32 a0, s32 a1) {
    func_002FC550(0x8000);
    sceCdLayerSearchFile(a0, a1, D_0035600C);
    return func_002FC550(0x8001);
}
