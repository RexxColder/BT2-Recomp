#include "common.h"

extern s32 func_00338920(s32 a0, s32 a1, s32 a2, s32 a3);

/* 0x00100248: tail call to func_00338920; a0..a3 pass through untouched. */
s32 func_00100248(s32 a0, s32 a1, s32 a2, s32 a3) {
    return func_00338920(a0, a1, a2, a3);
}
