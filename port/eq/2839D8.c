#include "common.h"

/* 0x002839D8: if (idx < 8) tail func_003126C8(&gGfxLens[idx] (0x30 bytes each), a1); else returns stale 3*idx. */
extern u8 gGfxLens[];
s32 func_003126C8(s32 arg0, s32 arg1);

s32 func_002839D8(u32 idx, s32 a1) {
    if (idx < 8) {
        return func_003126C8((s32)(gGfxLens + idx * 0x30), a1);
    }
    return (s32)(idx * 3);
}
