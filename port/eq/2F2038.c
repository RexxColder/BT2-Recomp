#include "common.h"

/* 0x002F2038: func_002F3378(a0); func_002F1FC8(a0); *(s32 *)(a0 + 0x5C) = 0xFFFFF; func_002F3390(); return 1. */
void func_002F3378(s32 arg0);
s32 func_002F1FC8(s32 arg0);
void func_002F3390();

s32 func_002F2038(s32 a0) {
    func_002F3378(a0);
    func_002F1FC8(a0);
    *(s32 *)((u8 *)a0 + 0x5C) = 0xFFFFF;
    func_002F3390();
    return 1;
}
