#include "m2c_macros.h"

void func_0026F118(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
f32 func_0026F148(void *arg0, s32 *arg1);
s32 Timer_Reset(void *arg0);
void func_002A1340(void);
void func_002A1590(s32 arg0);
void func_002A13E8(void);
void Font_SetScaleXY(f32 x, f32 y);
void Font_SetColorRGBA(u8 r, u8 g, u8 b, s32 a);
void func_002A15D0(s32 arg0);
void Font_SetShadowOffset(s32 dx, s32 dy);
void func_002A15F0(s32 packed);
void Font_PrintAt(s32 x, s32 y, void *text);

/* Draws a text entry from the table at arg4 (index arg5, offset in the low bits), scaled down to fit arg7. */
void Font_PrintFitted(void *arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 out[2];
    f32 scale;
    f32 alpha;
    s32 width;

    if (arg5 < 0) {
        return;
    }
    if (*arg1 < 0) {
        return;
    }
    func_0026F118(arg0, arg1, &out[0], &out[1]);
    alpha = func_0026F148(arg0, arg1);
    width = Timer_Reset(arg4 + (*(s32 *)(arg4 + arg5 * 4) & ~3));
    if (arg7 < width) {
        scale = (f32)arg7 / (f32)width;
    } else {
        scale = 1.0f;
    }
    func_002A1340();
    func_002A1590(arg6);
    Font_SetScaleXY(scale, 1.0f);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(alpha * 128.0f) & 0xFF);
    func_002A15D0(2);
    Font_SetShadowOffset(1, 2);
    func_002A15F0(((s32)(alpha * 64.0f) << 24) | 0x202020);
    Font_PrintAt(out[0] + arg2, out[1] + arg3, arg4 + (*(s32 *)(arg4 + arg5 * 4) & ~3));
    func_002A13E8();
}
