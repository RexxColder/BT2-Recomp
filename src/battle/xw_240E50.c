#include "common.h"

// Returns (s32)(table[arg1] * 30.0f), table = arg0->+0x1530 ->+0x98C, entries at +0x58 with 4-byte stride.
s32 func_00240E50(s32 arg0, s32 arg1) {
    s32 tbl = *(s32 *)(*(s32 *)((u8 *)arg0 + 0x1530) + 0x98C);
    f32 v = *(f32 *)(tbl + (arg1 * 4) + 0x58);
    return (s32)(v * 30.0f);
}
