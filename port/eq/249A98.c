#include "common.h"

void func_0026F118(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0026F148(s32 arg0, s32 arg1);
s32 func_002A1340();
void func_002A1590(s32 arg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002A15D0(s32 arg0);
s32 Font_SetShadowOffset(s32 arg0, s32 arg1);
void func_002A15F0(s32 arg0);
void Font_PrintNumAt(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002A13E8();

/* 0x00249A98: draws a number label. Returns at once when the first word at arg1 is negative;
 * otherwise reads a screen position through func_0026F118 (two out-words), takes a scale from
 * func_0026F148 and sets the font colour (alpha = scale * 128, truncated by cvt.w.s), the
 * shadow offset, and prints at (x + arg2, y + arg3) with arg4 as the value. */
void func_00249A98(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 xy[2];
    f32 f20;
    f32 t;
    s32 a;

    if (arg1[0] < 0) {
        return;
    }

    func_0026F118(arg0, (s32)arg1, (s32)&xy[0], (s32)&xy[1]);
    f20 = func_0026F148(arg0, (s32)arg1);
    func_002A1340();
    func_002A1590(arg5);

    t = f20 * 128.0f;
    a = (s32)t;
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, a & 0xFF);

    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);

    f20 = f20 * 64.0f;
    t = f20;
    a = (s32)t;
    func_002A15F0((s32)((u32)a << 24) | 0x202020);

    Font_PrintNumAt(xy[0] + arg2, xy[1] + arg3, arg4, 0);
    func_002A13E8();
}
