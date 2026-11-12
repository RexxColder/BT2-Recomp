#include "common.h"

/* 0x0028B058: writes 4 words into the gDmaCur buffer: (a1 >> 4) + 0x30000000, a0, 0, 0, then gDmaCur += 0x10. */
extern s32 D_00387EAC;

void func_0028B058(s32 a0, s32 a1) {
    u8 *p;

    p = (u8 *)D_00387EAC;
    *(s32 *)(p + 0x0) = (s32)(0x30000000 + ((u32)a1 >> 4));
    *(s32 *)(p + 0x4) = a0;
    *(s32 *)(p + 0x8) = 0;
    *(s32 *)(p + 0xC) = 0;
    D_00387EAC = (s32)(p + 0x10);
}
