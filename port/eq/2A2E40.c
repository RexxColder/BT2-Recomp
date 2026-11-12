#include "common.h"

extern s64 *func_002A2CD8(s32 arg0, s64 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
extern s8 D_00344C70[];

/* Draws button glyphs for a 16-bit text run: maps the leading symbol (arrows, circle, square,
   triangle, cross, full-width + / ( ) and L1-3 / R1-3 pairs) to an icon index, advances the
   string, draws it with func_002A2CD8 and moves x by the per-icon width. Stops at the first
   other character. */
void func_002A2E40(s32 gfx, s64 **out, s32 *px, s32 *py, u16 **str, s32 extra) {
    u16 *p = *str;

    while (*p != 0) {
        s32 idx = -1;
        s32 size = 0x20;
        u16 c = p[0];

        switch (c) {
        case 0x25B3: idx = 11; *str = p + 1; break;
        case 0x2191: idx = 4; *str = p + 1; break;
        case 0x2192: idx = 7; *str = p + 1; break;
        case 0x2193: idx = 5; *str = p + 1; break;
        case 0x2190: idx = 6; *str = p + 1; break;
        case 0xD7: idx = 10; *str = p + 1; break;
        case 0x25CB: idx = 8; *str = p + 1; break;
        case 0xFF0B: idx = 0; *str = p + 1; break;
        case 0xFF0F: idx = 1; *str = p + 1; break;
        case 0xFF08: idx = 2; *str = p + 1; break;
        case 0xFF09: idx = 3; *str = p + 1; break;
        case 0x25A1:
            *str = p + 1;
            idx = 9;
            if (p[1] == 0xFF0A) {
                *str = p + 3;
                idx = 18;
                size = 0x40;
            }
            break;
        case 0xFF2C:
            if (p[1] == 0xFF11) {
                idx = 12;
            } else if (p[1] == 0xFF12) {
                idx = 13;
            } else if (p[1] == 0xFF13) {
                idx = 14;
            }
            if (idx >= 0) {
                *str = p + 2;
            }
            break;
        case 0xFF32:
            if (p[1] == 0xFF11) {
                idx = 15;
            } else if (p[1] == 0xFF12) {
                idx = 16;
            } else if (p[1] == 0xFF13) {
                idx = 17;
            }
            if (idx >= 0) {
                *str = p + 2;
            }
            break;
        default:
            break;
        }
        if (idx < 0) {
            return;
        }
        *out = func_002A2CD8(gfx, *out, *px + D_00344C70[idx * 2], *py - 6, size, 0x20, idx, extra);
        *px += D_00344C70[idx * 2 + 1] + 3;
        p = *str;
    }
}
