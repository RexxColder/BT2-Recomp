#include "common.h"

s32 Font_IsNewline(s32 arg0);
s32 func_002A1A08(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002A2420(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 D_00387ED8;

/* 0x002A18F8: text step for character c = arg4 & 0xFFFF on the glyph record arg1. c == 0: returns 1. A newline
 * (Font_IsNewline): *arg2 = func_002A1A08(arg1, (s16) word +0xC, arg6, arg3, c); *arg3 += (int)((float)(D_00387ED8 +
 * (u16) +0x1A) * float +0x14); returns (byte flag word +0x3C & 1). Otherwise *arg2 += func_002A2420(arg0, arg1,
 * *arg2, *arg3, c, arg5) and returns 0. */
s32 func_002A18F8(u8 *arg0, u8 *arg1, s32 *arg2, s32 *arg3, s32 arg4, s32 arg5, s32 arg6) {
    u16 c = (u16)arg4;
    s32 v;

    if (c == 0) {
        return 1;
    }
    if (Font_IsNewline((s32)c) != 0) {
        *arg2 = func_002A1A08((s32)arg1, *(s16 *)(arg1 + 0xC), arg6, (s32)arg3, (s32)c);
        v = (s32)((f32)(D_00387ED8 + *(u16 *)(arg1 + 0x1A)) * *(f32 *)(arg1 + 0x14));
        *arg3 += v;
        if (*(s32 *)(arg1 + 0x3C) & 1) {
            return 1;
        }
        return 0;
    }
    v = func_002A2420((s32)arg0, (s32)arg1, *arg2, *arg3, (s32)c, arg5);
    *arg2 += v;
    return 0;
}
