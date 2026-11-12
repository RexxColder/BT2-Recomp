#include "common.h"

extern u8 *gEftVram;

s64 EftVram_AddImage(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;
    s32 n;
    s64 temp_v0;
    s64 temp_a1;
    u8 *t0;
    s32 a3;

    p = gEftVram;
    n = *(s32 *)(p + 0x800);
    *(s32 *)(p + n * 4) = arg0;
    *(s32 *)(p + n * 4 + 0x200) = *(s32 *)(p + 0x804);
    *(s32 *)(p + n * 4 + 0x400) = 0;
    *(s32 *)(p + n * 4 + 0x600) = 1;
    *(s32 *)(p + 0x800) = n + 1;
    temp_v0 = *(s64 *)((u8 *)arg0) & (((s64)0xFFF80003 << 32) | 0xFFFFC000);
    *(s64 *)((u8 *)arg0) = temp_v0;
    temp_v0 = temp_v0 | ((s64)arg2 << 35);
    t0 = *(u8 **)((u8 *)arg0 + 8);
    a3 = *(s32 *)(t0 + 0x10);
    temp_a1 = ((s64)arg1 << 34) | (s64)(*(u32 *)(p + 0x804));
    *(s32 *)(p + 0x804) = *(s32 *)(p + 0x804) + a3;
    return temp_v0 | temp_a1;
}
