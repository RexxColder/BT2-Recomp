#include "common.h"

extern u8 *D_00387B04;

/* 0x00283800 (sibling of 0x002837C0, 0x00283840): record arg0 (48 bytes each, table D_00387B04), field +0x20 =
 * packed colour (u8)arg1 | (u8)arg2 << 8 | (u8)arg3 << 16 | arg4 << 24 (the 5th argument is in t0). */
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 packed = (s32)((arg1 & 0xFF) | ((arg2 & 0xFF) << 8) | ((arg3 & 0xFF) << 16) | ((u32)arg4 << 24));

    *(s32 *)(D_00387B04 + arg0 * 48 + 0x20) = packed;
}
