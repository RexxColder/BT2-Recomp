#include "common.h"

s32 func_0020A6A0(s32 arg0);
extern void *D_003876A0;

/* Same test as BtlScene_IsCharStopped with the other callee: bit 8 of the word at +0x4D8 of D_003876A0, else the result of func_0020A6A0. */
s32 func_00126528(s32 arg0) {
    s32 r = (func_0020A6A0(arg0) != 0);
    s32 one = 1;
    return ((*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100) != 0) ? one : r;
}
