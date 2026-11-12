#include "common.h"

s32 func_0020A658(s32 arg0);
extern void *D_003876A0;

/* Stopped flag (bit 8 of the 64-bit word at +0x4D8 of the global at D_003876A0), else the result of func_0020A658. */
s32 BtlScene_IsCharStopped(s32 arg0) {
    s32 r = (func_0020A658(arg0) != 0);
    s32 one = 1;
    return ((*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100) != 0) ? one : r;
}
