#include "common.h"

/* 0x002A1610: gFontStyle (0x0038B910) +0x2A = a1 (halfword), +0x28 = a0 (halfword). */
extern u8 D_0038B910[];

void func_002A1610(s32 a0, s32 a1) {
    u8 *p;

    p = D_0038B910;
    *(s16 *)(p + 0x2A) = (s16)a1;
    *(s16 *)(p + 0x28) = (s16)a0;
}
