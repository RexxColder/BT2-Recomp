#include "common.h"

s32 func_0026F118(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0026F148(s32 arg0, s32 arg1);
s32 func_002A1340();
void func_002A1590(s32 arg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002A15D0(s32 arg0);
s32 Font_SetShadowOffset(s32 arg0, s32 arg1);
void func_002A15F0(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
s32 func_002A13E8();

/* 0x0024A598: sibling of 0x00249A98 (number label). Returns when arg5 or the first word at arg1 is
 * negative; reads a screen position through func_0026F118, takes a scale from func_0026F148, sets
 * the font colour (alpha = scale * 128) and the shadow, and prints at (x + arg2, y + arg3) the text
 * whose pointer is arg4 + (table[arg5] with its low two bits cleared). */
void func_0024A598(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6) {
    s32 xy[2];
    f32 f20;
    f32 t;
    s32 tv;

    if (arg5 < 0) {
        return;
    }
    if (arg1[0] < 0) {
        return;
    }

    func_0026F118(arg0, (s32)arg1, (s32)&xy[0], (s32)&xy[1]);
    f20 = func_0026F148(arg0, (s32)arg1);
    func_002A1340();
    func_002A1590(arg6);

    t = f20 * 128.0f;
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, ((s32)t) & 0xFF);

    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);

    f20 = f20 * 64.0f;
    func_002A15F0((s32)(((u32)(s32)f20 << 24) | 0x202020));

    tv = *(s32 *)(arg4 + arg5 * 4);
    Font_PrintAt(xy[0] + arg2, xy[1] + arg3, (s32)(arg4 + (((u32)tv >> 2) << 2)));
    func_002A13E8();
}
