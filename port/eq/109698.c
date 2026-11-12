#include "common.h"

s32 Font_GetGlyphHeight(u8 *arg0);
s32 func_00108780(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_00109818(s32 arg0);

/* arg1 is never read (the asm passes its own a1 on to Font_GetGlyphHeight, which ignores it). */
s32 func_00109698(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s0;
    s32 h;
    s32 t0;
    s32 t2;
    s32 v0;
    s32 v1;
    s32 r1;
    s32 r2;
    s32 r4;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    s1 = arg3;
    s2 = arg4;
    s3 = arg2;
    s5 = arg5;

    h = Font_GetGlyphHeight(arg0);
    t0 = s2 - s1;
    t2 = h * 8 + h;
    s0 = (t0 + (s32)((u32)t0 >> 31)) >> 1;
    t0 = t0 - s0;
    s4 = t2 * 2;
    r1 = func_00108780((s32)arg0, s3, s1, 9, t0, 0x21);
    r2 = func_00108780(r1, s3, s2, 9, -s0, 0x21);
    s1 = s1 + 2;
    v0 = func_00109818(r1);
    s0 = r2;
    v0 = v0 + s4;
    f3 = (f32)v0;
    s2 = s2 - 2;
    s3 = s3 + 2;
    t0 = s2 - s1;
    f0 = 0.0f;
    if (0.0f < f3) {
        f2 = (f32)t0;
        f0 = (f32)s5 * f2;
        f1 = (f32)s4 * f2;
        f0 = f0 / f3;
        f1 = f1 / f3;
        s1 = s1 + (s32)f0;
        v1 = (s32)f1;
        s2 = s1 + v1;
        t0 = s2 - s1;
    }
    v0 = t0;
    v1 = (t0 + (s32)((u32)t0 >> 31)) >> 1;
    s0 = v1;
    t0 = t0 - s0;
    r4 = func_00108780(r2, s3, s1 - 0x1B, 5, t0 + 0x1B, 0x22);
    return func_00108780(r4, s3, s2 + 0x1B, 5, -(s0 + 0x1B), 0x22);
}
