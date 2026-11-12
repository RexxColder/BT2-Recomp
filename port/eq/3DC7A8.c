#include "common.h"

extern u8 D_00427340[] __attribute__((section(".data")));

void *memcpy(void *dst, const void *src, u32 n);
f32 func_26F148(s32 a0, u8 *a1);
void func_26F118(s32 a0, u8 *a1, s32 *a2, s32 *a3);
s32 Font_GetGlyphHeight(void);
void func_2A1340(s32 a0, s32 a1, s32 a2);
void func_2A1590(s32 a0);
void func_2A1508(s32 a0, s32 a1);
void Font_SetClip(s32 a0, s32 a1, s32 a2, s32 a3);
void Font_SetColorRGBA(s32 a0, s32 a1, s32 a2, s32 a3);
void func_2A15D0(s32 a0);
void Font_SetShadowOffset(s32 a0, s32 a1);
void func_2A15F0(s32 a0);
void Font_PrintAt(s32 a0, s32 a1, u8 *text);
void func_2A13E8(void);

/* 0x003DC7A8: draws one line of text. w[4..5] is a copy of the 8 bytes at D_00427340. Returns when t1 < 0 or *a1 < 0.
 * func_26F118(a0, a1, &w[0], &w[1]) and f20 = func_26F148(a0, a1). X = w[0] + a2, Y = w[1] + a3 are stored back to
 * w[0] / w[1]; w[8] = X - w[4], w[9] = Y - w[5] (+2 before the print), w[10] = 0x200, w[11] = h * s8 + w[5] * (s8 - 1)
 * + Y with h = Font_GetGlyphHeight(). Then func_2A1340, func_2A1590(t2), func_2A1508(w[4], w[5]), Font_SetClip,
 * Font_SetColorRGBA(255, 255, 255, (int)(f20 * 128) & 0xFF), func_2A15D0(2), Font_SetShadowOffset(1, 2),
 * func_2A15F0(((int)(f20 * 64) << 24) | 0x202020), Font_PrintAt(X, Y - t3, t0 + ((*(t0 + 4 * t1) >> 2) << 2)). */
void func_003DC7A8(s32 a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, s32 t2, s32 t3, s32 s8) {
    s32 w[12];
    f32 f20;
    s32 h;
    s32 x1;
    s32 y1;

    memcpy(&w[4], D_00427340, 8);
    if (t1 < 0) {
        return;
    }
    if (*(s32 *)a1 < 0) {
        return;
    }
    func_26F118(a0, a1, &w[0], &w[1]);
    f20 = func_26F148(a0, a1);
    x1 = w[0] + a2;
    y1 = w[1] + a3;
    w[0] = x1;
    w[1] = y1;
    w[8] = x1 - w[4];
    w[9] = y1 - w[5];
    w[10] = 0x200;
    h = Font_GetGlyphHeight();
    w[9] = w[9] + 2;
    w[11] = h * s8 + w[5] * (s8 - 1) + y1;
    func_2A1340(w[5] * (s8 - 1), s8 - 1, y1);
    func_2A1590(t2);
    func_2A1508(w[4], w[5]);
    Font_SetClip(w[8], w[9], w[10], w[11]);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, (s32)(f20 * 128.0f) & 0xFF);
    func_2A15D0(2);
    Font_SetShadowOffset(1, 2);
    f20 = f20 * 64.0f;
    func_2A15F0((s32)(((u32)(s32)f20) << 24) | 0x202020);
    Font_PrintAt(w[0], y1 - t3, t0 + (((*(u32 *)(t0 + 4 * t1)) >> 2) << 2));
    func_2A13E8();
}
