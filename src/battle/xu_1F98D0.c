#include "common.h"
s32 func_001F9568(s32 arg0);
extern void *D_00387930;
s32  func_001F98D0(s32 arg0) {
    s32 idx = func_001F9568(arg0);
    u8 *tab = (u8 *)*(s32 *)((u8 *)D_00387930 + 0x1C);
    s16 r = *(s16 *)(tab + (0x31 - idx) * 2 + 0x190);
    return (s16)(r);
}
