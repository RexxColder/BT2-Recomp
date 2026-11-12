#include "common.h"

extern s32 D_00388728[];
extern s32 func_00126560();

/* 0x00148A80: if func_00126560() is nonzero, table[a0 * 6 + a1] = a2 and return the byte offset (stale v0); else 0. */
s32 func_00148A80(s32 a0, s32 a1, s32 a2) {
    s32 r = func_00126560();
    s32 off;

    if (r == 0) {
        return r;
    }
    off = (a0 * 6 + a1) * 4;
    D_00388728[a0 * 6 + a1] = a2;
    return off;
}
