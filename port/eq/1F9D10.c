#include "common.h"

/* 0x001F9D10: if (a0->+0x8EC != a1) { func_0025FA60(a0->+0x152C); func_001F9A20(a0->+0x1530->+0xBFC, a1); }
   a0->+0x8EC = a1. */
void func_0025FA60(s32 arg0, s32 arg1);
void func_001F9A20(s32 arg0, s32 arg1);

void func_001F9D10(s32 a0, s32 a1) {
    u8 *p;

    if (*(s32 *)((u8 *)a0 + 0x8EC) != a1) {
        func_0025FA60(*(s32 *)((u8 *)a0 + 0x152C), a1);
        p = *(u8 **)((u8 *)a0 + 0x1530);
        func_001F9A20(*(s32 *)(p + 0xBFC), a1);
    }
    *(s32 *)((u8 *)a0 + 0x8EC) = a1;
}
