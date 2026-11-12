#include "common.h"

extern void *gEftVram;

void func_001F3A60(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s64 t4;
    s32 n;

    /* 0xFFF80003 << 16, then 0xFFFF, << 16, then 0xC000 (64-bit mask built by shifts and ORs) */
    t4 = (s64)(s32)0xFFF80000;
    t4 |= 0x0003;
    t4 <<= 16;
    t4 |= 0xFFFF;
    t4 <<= 16;
    t4 |= 0xC000;

    n = *(s32 *)((u8 *)gEftVram + 0x800);
    *(s32 *)((u8 *)gEftVram + n * 4) = (s32)(long)arg0;
    *(s32 *)((u8 *)gEftVram + n * 4 + 0x200) = arg1;
    *(s32 *)((u8 *)gEftVram + n * 4 + 0x400) = arg2;
    *(s32 *)((u8 *)gEftVram + n * 4 + 0x600) = 3;
    *(s64 *)arg0 = *(s64 *)arg0 & t4;
    /* The shifted-OR values computed after the stores are never stored: dead. */
    *(s32 *)((u8 *)gEftVram + 0x800) = *(s32 *)((u8 *)gEftVram + 0x800) + 1;
}
