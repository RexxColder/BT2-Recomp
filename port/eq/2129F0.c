#include "common.h"

extern u8 *D_00387930;

/* 0x002129F0 BtlChar_FrameMod: word at +0x20 of D_00387930, modulo arg0 (1 when arg0 <= 0). */
s32 BtlChar_FrameMod(s32 arg0) {
    s32 d = (arg0 <= 0) ? 1 : arg0;

    return *(s32 *)(D_00387930 + 0x20) % d;
}
