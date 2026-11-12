#include "common.h"

s32 func_2A0EA8(u8 *a0);
void func_26F118(s32 a0, u8 *a1, s32 *a2, s32 *a3);
f32 func_26F148(s32 a0, u8 *a1);
void func_2A1340(void);
void func_2A1590(s32 a0);
void Font_SetColorRGBA(s32 a0, s32 a1, s32 a2, s32 a3);
void func_2A15D0(s32 a0);
void Font_SetShadowOffset(s32 a0, s32 a1);
void func_2A15F0(s32 a0);
void Font_PrintAt(s32 a0, s32 a1, u8 *text);
void func_2A13E8(void);

/* 0x0041C8D8: text line draw, the sibling of 0x3DC7A8 without the copy or Font_SetClip. Returns when t1 < 0 or *a1 < 0.
 * (X, Y) = func_26F118 out words; r = func_2A0EA8(t0 + 4-aligned word at t0 + 4 * t1): r == 1 adds 10 to Y. Then
 * func_2A1340, func_2A1590(t2), Font_SetColorRGBA(t3 >> 24, (t3 >> 16) & 0xFF, (t3 >> 8) & 0xFF, (int)(f20 * (t3 & 0xFF))
 * & 0xFF) with f20 = func_26F148(a0, a1), func_2A15D0(2), Font_SetShadowOffset(1, 2), func_2A15F0 with the stack
 * colour, and Font_PrintAt(X + a2 + 6, Y + a3, t0 + the aligned word). */
void func_0041C8D8(s32 a0, u8 *a1, s32 a2, s32 a3, u8 *t0, s32 t1, s32 t2, s32 t3, s32 s5) {
    s32 sp[2];
    f32 f20;
    f32 f;
    u32 col;
    u32 q;
    u32 v;
    s32 off;

    if (t1 < 0) {
        return;
    }
    if (*(s32 *)a1 < 0) {
        return;
    }
    func_26F118(a0, a1, &sp[0], &sp[1]);
    f20 = func_26F148(a0, a1);
    off = (s32)(((*(u32 *)(t0 + 4 * t1)) >> 2) << 2);
    if (func_2A0EA8(t0 + off) == 1) {
        sp[1] = sp[1] + 10;
    }
    func_2A1340();
    func_2A1590(t2);
    col = (u32)t3;
    f = (f32)(s32)(col & 0xFF) * f20;
    Font_SetColorRGBA((s32)(col >> 24), (s32)((col >> 16) & 0xFF), (s32)((col >> 8) & 0xFF), (s32)f & 0xFF);
    func_2A15D0(2);
    Font_SetShadowOffset(1, 2);
    f = (f32)(s32)((u32)s5 & 0xFF) * f20;
    q = (u32)s5 >> 8;
    v = ((q & 0xFF) << 16) | (q & 0xFF00);
    func_2A15F0((s32)((((u32)s5) >> 24) | (((u32)(s32)f) << 24) | v));
    Font_PrintAt(sp[0] + a2 + 6, sp[1] + a3, t0 + off);
    func_2A13E8();
}
