#include "common.h"
s32 func_001F95C0(s32 arg0);
extern void *D_00387930;
s32 func_001F9940(s32 arg0) {
    s32 idx = func_001F95C0(arg0);
    u8 *tab = (u8 *)*(s32 *)((u8 *)D_00387930 + 0x1C);
    u8 *p = tab + (0x281 - idx);
    return p[8];
}
