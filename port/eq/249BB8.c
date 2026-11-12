#include "common.h"

void func_0026F118(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0026F148(void *arg0, s32 *arg1);
void func_002A1340(void);
void func_002A1590(s32 arg0);
void func_002A13E8(void);
s32 func_002A15D0(s32 arg0);
void func_002A15F0(s32 arg0);
s32 Timer_Reset(s32 arg0);
s32 Font_SetScaleXY(f32 farg0, f32 farg1);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);

/* 0x00249BB8: when *arg1 >= 0: lay out the text at the object offsets (26F118 fills ox, oy; 26F148 gives the alpha),
 * set the scale from the timer (225 / timer when 225 < timer, else 1.0), font colour (alpha * 128), shadow (1, 2),
 * style 0x202020 with alpha * 64 in the top byte, then print at (ox + 246 or ox + 10, oy) (arg6 == 2 selects 246).
 * arg4 is the table base (t0), arg5 the index (t1), arg6 the mode (t2, passed to func_002A1590). Returns *arg1 when
 * it is negative. The positive path returns the stale v0 of func_002A13E8 (void): 0 here, not modelled. */
s32 func_00249BB8(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6) {
    s32 *slot = (s32 *)(arg4 + 4 * arg5);
    u8 *timerPtr = arg4 + (((u32)slot[1] >> 2) << 2);
    s32 ox;
    s32 oy;
    s32 timer;
    f32 alpha;
    f32 scale;

    if (*arg1 < 0) {
        return *arg1;
    }

    func_0026F118((s32)arg0, (s32)arg1, (s32)&ox, (s32)&oy);
    alpha = func_0026F148(arg0, arg1);
    timer = Timer_Reset((s32)timerPtr);
    if (225 < timer) {
        scale = 225.0f / (f32)timer;
    } else {
        scale = 1.0f;
    }

    func_002A1340();
    func_002A1590(arg6);
    Font_SetScaleXY(scale, 1.0f);
    Font_SetColorRGBA(255, 255, 255, (u8)(s32)(alpha * 128.0f));
    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);
    func_002A15F0(((s32)(alpha * 64.0f) << 24) | 0x202020);
    if (arg6 == 2) {
        Font_PrintAt(ox + arg2 + 246, oy + arg3, (s32)timerPtr);
    } else {
        Font_PrintAt(ox + arg2 + 10, oy + arg3, (s32)timerPtr);
    }
    func_002A13E8();
    return 0;
}
