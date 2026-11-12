#include "common.h"

s32 func_002411A0(s32 arg0, s32 arg1);

// Calls func_002411A0(arg0, arg1), then returns (s32)(f * 30.0f) for the float at +0x48 of table entry
// (arg0->+0x1530->+0x980 + index * 4), where index is the call's result.
s32 func_00241250(s32 arg0, s32 arg1) {
    s32 idx = func_002411A0(arg0, arg1);
    s32 obj = *(s32 *)((u8 *)arg0 + 0x1530);
    s32 tbl = *(s32 *)((u8 *)obj + 0x980);
    f32 f = *(f32 *)(tbl + (idx * 4) + 0x48);
    return (s32)(f * 30.0f);
}
