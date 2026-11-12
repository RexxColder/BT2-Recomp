#include "common.h"

void func_26F118(s32 a0, u8 *a1, s32 *a2, s32 *a3);
f32 func_26F148(s32 a0, u8 *a1);
s32 func_2A0EA8(u8 *a0);
void func_2A1340(void);
void Font_SetColorRGBA(s32 a0, s32 a1, s32 a2, s32 a3);
void func_2A15D0(s32 a0);
void Font_SetShadowOffset(s32 a0, s32 a1);
void func_2A15F0(s32 a0);
void Font_PrintAt(s32 a0, s32 a1, u8 *text);
void func_2A13E8(void);

/* 0x003EA5D8: draws one text line. p (a1) must have a non-negative word at 0; tbl (t0) holds u32 entries
 * (text offset in the low bits of word 1 of each 8-byte entry at tbl + idx * 4 + 4). The frame words fr[0], fr[1]
 * are offset by 0x10/0x80 (flag) and by a per-type value; color (t3) is the RGBA word, shadow (stack) the second one.
 * Line placement uses func_26F118 / func_26F148 (returns the scale f32). */
void func_003EA5D8(s32 x, u8 *p, s32 ya, s32 yb, u8 *tbl, s32 idx, s32 flag, u32 color, u32 shadow) {
    s32 fr[2];
    s32 ty;
    f32 scale;
    f32 alpha;
    u32 w;
    u32 v;

    if (idx < 0) {
        return;
    }
    if (*(s32 *)p < 0) {
        return;
    }
    func_26F118(x, p, &fr[0], &fr[1]);
    scale = func_26F148(x, p);

    if (flag != 0) {
        fr[0] += 0x80;
    } else {
        fr[0] += 0x10;
    }

    w = *(u32 *)(tbl + idx * 4 + 4) & ~3u;
    ty = func_2A0EA8(tbl + w);
    if (ty == 2) {
        fr[1] += 0x1C;
    } else if (ty == 1) {
        fr[1] += 0x24;
    } else if (ty == 3) {
        fr[1] += 0x10;
    } else if (ty == 4) {
        fr[1] += 0x6;
    }

    func_2A1340();

    alpha = (f32)(color & 0xFF) * scale;
    Font_SetColorRGBA(color >> 24, (color >> 16) & 0xFF, (color >> 8) & 0xFF, (s32)alpha & 0xFF);
    func_2A15D0(1);
    Font_SetShadowOffset(1, 2);

    alpha = (f32)(shadow & 0xFF) * scale;
    v = shadow >> 8;
    func_2A15F0((shadow >> 24) | ((u32)(s32)alpha << 24) | ((v & 0xFF) << 16) | (v & 0xFF00));

    w = *(u32 *)(tbl + idx * 4 + 4) & ~3u;
    Font_PrintAt(fr[0] + ya, fr[1] + yb, tbl + w);
    func_2A13E8();
}
