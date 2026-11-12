#include "common.h"

s32 func_002411A0(s32 arg0, s32 arg1);
/* ctx.h says two arguments; the call site passes arg0, a 64-bit constant 0x8000 << 21 and the object. */
s32 func_00203C58(s32 arg0, s64 arg1, s32 arg2);

// Calls func_002411A0 for an index, reads the word at +0x54 of that entry (arg0->+0x1530->+0x980), then calls
// func_00203C58; the word is halved only when that call returns nonzero.
s32 func_00241718(s32 arg0, s32 arg1) {
    s32 idx = func_002411A0(arg0, arg1);
    s32 obj = *(s32 *)((u8 *)arg0 + 0x1530);
    s32 tbl = *(s32 *)((u8 *)obj + 0x980);
    s32 word = *(s32 *)((u8 *)tbl + (idx * 4) + 0x54);
    s32 r = func_00203C58(arg0, (s64)0x8000 << 21, obj);
    if (r != 0) {
        word = word / 2;
    }
    return word;
}
