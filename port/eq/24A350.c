#include "common.h"

void func_0026F118(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_0026F148(s32 arg0, s32 arg1);
s32 Timer_Reset(s32 arg0);
void func_002A1340();
void func_002A1590(s32 arg0);
s32 Font_SetScaleXY(f32 farg0, f32 farg1);
void func_002A15D0(s32 arg0);
void Font_SetColorRGBA(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Font_SetShadowOffset(s32 arg0, s32 arg1);
void func_002A15F0(s32 arg0);
void Font_PrintAt(s32 arg0, s32 arg1, s32 arg2);
void func_002A13E8();

/* 0x0024A350: draws a text line. flags (arg5) indexes a table of u32 offsets at base;
 * the offset (rounded down to 4) is the timer/text block. color (arg8) and color2 (arg9)
 * carry RGBA bytes; the alpha byte is scaled by the func_0026F148 factor. */
void func_0024A350(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *base, s32 flags,
                   s32 arg6, s32 arg7, u32 color, u32 color2)
{
    s32 out[2];
    s32 *slot;
    s32 timerRet;
    f32 scale;
    f32 alphaScale;
    s32 alpha;
    u32 packed;

    if (flags < 0) {
        return;
    }
    if (*(s32 *)arg1 < 0) {
        return;
    }

    func_0026F118((s32)arg0, (s32)arg1, (s32)&out[0], (s32)&out[1]);
    scale = func_0026F148((s32)arg0, (s32)arg1);

    slot = (s32 *)(base + 4 * flags);
    timerRet = Timer_Reset((s32)(base + (((u32)*slot >> 2) << 2)));
    if (arg7 < timerRet) {
        alphaScale = (f32)arg7 / (f32)timerRet;
    } else {
        alphaScale = 1.0f;
    }

    func_002A1340();
    func_002A1590(arg6);
    Font_SetScaleXY(alphaScale, 1.0f);

    alpha = (s32)((f32)(color & 0xFF) * scale);
    Font_SetColorRGBA((s32)(color >> 24), (s32)((color >> 16) & 0xFF),
                      (s32)((color >> 8) & 0xFF), alpha & 0xFF);
    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);

    alpha = (s32)((f32)(color2 & 0xFF) * scale);
    packed = ((u32)alpha << 24) | (((color2 >> 8) & 0xFF) << 16)
           | ((color2 >> 8) & 0xFF00) | (color2 >> 24);
    func_002A15F0((s32)packed);

    slot = (s32 *)(base + 4 * flags);
    Font_PrintAt(out[0] + arg2, out[1] + arg3,
                 (s32)(base + (((u32)*slot >> 2) << 2)));
    func_002A13E8();
}
