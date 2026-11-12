#include "common.h"

/* 0x002FC550: D_003553A0 = D_003553A4 (old value); D_003553A4 = a0. Returns &D_003553A0 (left in v0). */
extern s32 D_003553A0;
extern s32 D_003553A4;

s32 func_002FC550(s32 a0) {
    s32 old;

    old = D_003553A4;
    D_003553A0 = old;
    D_003553A4 = a0;
    return (s32)&D_003553A0;
}
