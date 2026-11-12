#include "common.h"

s32 func_002FA088(s32 a0);

/* 0x002F3010: *out = func_002FA088(a0); return 1. */
s32 func_002F3010(s32 a0, s32 *out) {
    *out = func_002FA088(a0);
    return 1;
}
