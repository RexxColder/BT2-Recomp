#include "common.h"

#define U16AT(p) (*(u16 *)(p))

s32 func_001081C0();
s32 Font_GetGlyphHeight(void);
void func_002A1340(void);
void func_002A15B0(s32 arg0);
s32 func_002A15D0(s32 arg0);
void func_002A13E8(void);
s32 Font_SetScaleXY(f32 x, f32 y);
void Font_SetColorRGBA(s32 r, s32 g, s32 b, s32 a);
void func_002A1678(s32 a0, s32 a1, s32 a2, s32 a3);
void Font_SetClip(s32 x0, s32 y0, s32 x1, s32 y1);
void Font_PrintAt(s32 x, s32 y, u8 *text);
s32 func_00108DC0(s32 colorIdx, s32 count, s32 bank);
u8 *func_00108910(u8 *dl, s32 x, s32 y, s32 ch);
u8 *func_00108780(u8 *dl, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
u8 *func_00108A60(u8 *dl, s32 x, s32 y, u8 *text, s32 line);
u8 *BtlText_NextLine(u8 *text);

extern u8 *D_00387F2C;
extern f32 D_003876C0;

#define COL(v) ((s32)(u8)(s32)(v))

u8 *func_00108E98(u8 *dl, s32 x, s32 xr, s32 ya, s32 yb, s32 scroll, s32 bank) {
    u8 *text;
    s32 y;
    s32 lineH;
    s32 running;
    s32 line;
    s32 colorIdx;
    s32 cnt;
    s32 prev;
    s32 c;
    s32 w;
    f32 f;

    text = (u8 *)func_001081C0();
    y = ya - scroll;
    lineH = Font_GetGlyphHeight() * 20;
    func_002A1340();
    func_002A15B0(1);
    running = 1;
    line = 0;
    Font_SetScaleXY(1.0f, 1.0f);
    func_002A15D0(2);
    Font_SetColorRGBA(0xFF, 0xFF, 0xFF, 0x80);
    colorIdx = -1;
    func_002A1678(0, 0x10, 0x10, 0x40);
    cnt = 0;
    Font_SetClip(x, ya, xr - 1, yb - 1);
    *(u64 *)(dl + 0) = 0x1000000000008001ULL;
    *(u64 *)(dl + 8) = 0xE;
    dl += 0x10;
    *(u64 *)(dl + 8) = 0x40;
    *(u64 *)(dl + 0) = (u64)(s64)x | (((u64)(s64)(yb - 1)) << 48) |
                       (((u64)(s64)ya << 32) | ((u64)((s64)(xr - 1) << 16)));
    dl += 0x10;
    w = lineH - 0xC;
    c = U16AT(text);
    prev = 0;

    for (;;) {
        if (c == 0x26) {
            s32 d1 = U16AT(text + 2);
            s32 d2 = U16AT(text + 4);
            s32 d3 = U16AT(text + 6);
            s32 idx = d1 * 100 + d2 * 10 + d3;
            text += 8;
            if (*(s16 *)(D_00387F2C + idx * 4 - 0x340E) <= 0) {
                D_003876C0 = 0.25f;
            }
            c = U16AT(text);
        }
        if (c == 0x24) {
            cnt = -1;
            colorIdx = U16AT(text + 2) - 0x30;
        } else if (c == 0x25) {
            if ((U16AT(text + 2) ^ 0x30) == 0) {
                cnt = cnt + 1;
            }
        }
        if (c != 0x24) {
            if (func_00108DC0(colorIdx, cnt, bank) != 0) {
                D_003876C0 = 0.25f;
            }
        }
        c = U16AT(text);

        if (c == 0x24) {
            y += (line != 0) ? 0xC : 6;
            if (ya < y + 0x20 && y < yb) {
                dl = func_00108910(dl, x, y - 3, U16AT(text + 2));
                f = D_003876C0;
                Font_SetColorRGBA(COL(f * 252.0f), COL(f * 245.0f), COL(f * 222.0f), 0x80);
                f = D_003876C0;
                func_002A1678(COL(f * 135.0f), COL(f * 79.0f), COL(f * 20.0f), 0x80);
                Font_PrintAt(x + 0x1A, y + 3, text + 4);
            }
        } else if (c == 0x25) {
            s32 k = U16AT(text + 2);
            if (k == 0x30) {
                y += 6;
                if (ya < y + 0x20 && y < yb) {
                    s32 z;
                    f = D_003876C0;
                    Font_SetColorRGBA(COL(f * 253.0f), COL(f * 251.0f), COL(f + f), 0x80);
                    f = D_003876C0;
                    z = COL(f * 0.0f);
                    func_002A1678(z, z, COL(f * 64.0f), 0x40);
                    Font_PrintAt(x + 0x14, y + 3, text + 4);
                    dl = func_00108780(dl, x + 9, y, w, 0x1C, 0x1F);
                    dl = func_00108780(dl, x - 6, y, w, 0x1C, 0x20);
                }
            } else if (k == 0x31 || k == 0x32 || k == 0x33) {
                if (prev == 0x24) {
                    y += 6;
                }
                if (ya < y + 0x20 && y < yb) {
                    s32 z;
                    if (k == 0x31) {
                        f = D_003876C0;
                        Font_SetColorRGBA(COL(f * 93.0f), COL(f * 245.0f), COL(f * 247.0f), 0x80);
                        f = D_003876C0;
                        z = COL(f * 0.0f);
                        func_002A1678(z, z, COL(f * 64.0f), 0x40);
                        Font_PrintAt(x + 0x28, y + 3, text + 4);
                        dl = func_00108780(dl, x + 0x1D, y, lineH - 0xC, 0x1C, 0x1E);
                    } else if (k == 0x32) {
                        s32 g;
                        f = D_003876C0;
                        g = COL(f * 89.0f);
                        Font_SetColorRGBA(COL(f * 239.0f), g, g, 0x80);
                        f = D_003876C0;
                        z = COL(f * 0.0f);
                        func_002A1678(COL(f * 64.0f), COL(f * 17.0f), z, 0x40);
                        Font_PrintAt(x + 0x28, y + 3, text + 4);
                        dl = func_00108780(dl, x + 0x1D, y, lineH - 0xC, 0x1C, 0x1E);
                    } else {
                        s32 g;
                        f = D_003876C0;
                        g = COL(f * 255.0f);
                        Font_SetColorRGBA(g, g, g, 0x80);
                        f = D_003876C0;
                        g = COL(f * 0.0f);
                        func_002A1678(g, g, g, 0x40);
                        Font_PrintAt(x + 0x28, y + 3, text + 4);
                        dl = func_00108780(dl, x + 0x1D, y, lineH - 0xC, 0x1C, 0x1E);
                    }
                }
            }
        } else if (c == 0x23) {
            if (ya < y + 0x20 && y < yb) {
                if (U16AT(text + 2) != 0x30) {
                    dl = func_00108A60(dl, x + 0x18, y - 5, text + 2, line);
                }
            }
        } else if (c == 0x40) {
            running = 0;
        } else {
            if (ya < y + 0x20 && y < yb) {
                Font_PrintAt(x + 0x14, y + 3, text);
            }
        }

        y += 0x19;
        line = line + 1;
        D_003876C0 = 1.0f;
        prev = U16AT(text);
        text = BtlText_NextLine(text);
        c = U16AT(text);
        if (c == 0 || running == 0) {
            break;
        }
    }

    func_002A13E8();
    *(u64 *)(dl + 0) = 0x1000000000008001ULL;
    *(u64 *)(dl + 8) = 0xE;
    dl += 0x10;
    *(u64 *)(dl + 0) = 0x01BF000001FF0000ULL;
    *(u64 *)(dl + 8) = 0x40;
    return dl + 0x10;
}
