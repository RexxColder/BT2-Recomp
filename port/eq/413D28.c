#include "common.h"

/* Menu overlay: character/form/colour select screen, draws the Flash layers each frame. */
extern u8 *D_0042BB7C;  /* menu work area */

void func_00277E70(u8 *dst, s32 val, s64 n);
void func_0026EBC0(u8 *layer, const char *name, u8 *ref);
void func_0026EC48(u8 *layer, u8 *ref, s32 *rect);
void func_0026EFC8(u8 *layer, u8 *ref, s32 prop);
void func_0026EEF8(u8 *layer, u8 *ref, f32 f12);
void func_0026EEC8(u8 *layer, u8 *ref, s32 x, s32 y);
void func_0026EF88(u8 *layer, u8 *ref, f32 f12);
f32 func_0026F148(u8 *layer, u8 *ref);
void func_0026EB20(u8 *layer, s32 a1, s32 a2);
s32 func_0026EA58(u8 *layer);
void func_00249BB8(u8 *layer, u8 *ref, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_00249DB8(u8 *layer, u8 *ref, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
s32 func_00325830(u8 *buf, const char *fmt, ...);

#define W32(off) (*(s32 *)(D_0042BB7C + (off)))

s32 func_00413D28(void) {
    /* 5-int rectangles: x0, y0, x1, y1, unused */
    s32 typeRects[15] = {0, 0, 256, 32, 0, 0, 32, 256, 64, 0, 0, 64, 256, 92, 0};
    char typeNames[3][255] = {"mc_type_text_normal", "mc_type_text_custom", "mc_type_text_evoz"};
    s32 colorRects[30] = {0,  0,  32, 32, 0,  32, 0,  64, 32, 0,  64, 0,  96, 32, 0,
                          0,  32, 32, 64, 0,  32, 32, 64, 64, 0,  64, 32, 96, 64, 0};
    s32 arrowRect[5] = {0, 32, 32, 64, 0};
    s32 rc[4];
    s32 btnRect[4];
    u8 ref[16];
    u8 nameRef[16];
    u8 formRef[16];
    u8 typeRef[16];
    u8 colorRef[16];
    u8 nameBuf[128];
    s32 sel[2];
    s32 side;
    s32 j;
    s32 m;
    s32 idx;
    s32 val;
    s32 col;
    s32 prop;
    s32 mode;
    s32 cell;
    s32 row;
    s32 offX;
    s32 offY;
    s32 lvl;
    s32 cur;
    u8 *layer60;
    u8 *layer;
    u8 *tbl;
    f32 sc;
    s32 r;
    const char *nm;

    func_00277E70(*(u8 **)(D_0042BB7C + 0x128), 0, 128);
    layer60 = D_0042BB7C + 0x60;

    /* tag arrows: blend grows while the flag bit is held */
    for (side = 0; side < 2; side++) {
        for (j = 0; j < 2; j++) {
            f32 *bl = (f32 *)(D_0042BB7C + 0x374C + 8 * side + 4 * j);
            if ((W32(0x22C + 4 * side) & (0x40 << j)) != 0) {
                *bl = *bl + 0x1.333332p-4f;
                if (1.0f <= *bl) {
                    *bl = 1.0f;
                }
            } else {
                *(s32 *)bl = 0;
            }
            if (side != 0) {
                nm = j ? "mc_tag_chara_l_down" : "mc_tag_chara_r1";
            } else {
                nm = j ? "mc_tag_chara_r_up" : "mc_tag_chara_l1";
            }
            func_0026EBC0(layer60, nm, ref);
            func_0026EEF8(layer60, ref, *(f32 *)(D_0042BB7C + 0x374C + 8 * side + 4 * j));
        }
    }

    /* name / form text plates */
    for (side = 0; side < 2; side++) {
        for (j = 0; j < 2;) {
            u8 *p = D_0042BB7C + 8 * side + 4 * j;
            col = *(s32 *)(p + 0x26C);
            if (*(s32 *)(p + 0x23C) + 7 * *(s32 *)(p + 0x24C) >= 74) {
                col = 132;
            }
            if (side == 0) {
                func_0026EBC0(layer60, j ? "mc_name_text_l_up" : "mc_name_text_r_up", nameRef);
                func_0026EBC0(layer60, j ? "mc_form_text_l_up" : "mc_form_text_r_up", formRef);
                prop = j ? 0 : 2;
            } else {
                func_0026EBC0(layer60, j ? "mc_name_text_r_down" : "mc_name_text_l_down", nameRef);
                func_0026EBC0(layer60, j ? "mc_form_text_r_down" : "mc_form_text_l_down", formRef);
                prop = j ? 2 : 0;
            }
            if (j == 1 && W32(0x29C + 4 * side) == 0) {
                j = 2;
            } else {
                func_00249BB8(layer60, nameRef, 0, 0, W32(0x2C), col, prop);
                func_00249DB8(layer60, formRef, 0, 0, W32(0x30), col, prop);
                j++;
            }
        }
    }
    func_0026EBC0(layer60, "mc_name_plate_turn", ref);
    func_0026EFC8(layer60, ref, 16);
    func_0026EBC0(layer60, "mc_name_plate_turn2", ref);
    func_0026EFC8(layer60, ref, 16);

    /* type text */
    for (side = 0; side < 2; side++) {
        layer = D_0042BB7C + 0xD8 + 40 * side;
        func_0026EB20(layer, 0, side ? 253 : 44);
        func_0026EBC0(layer, "mc_type_text_onanime", typeRef);
        func_0026EEC8(layer, typeRef, 0, 22 * W32(0x27C + 4 * side));
        func_0026EBC0(layer, typeNames[W32(0x27C + 4 * side)], ref);
        sc = func_0026F148(layer, ref);
        func_0026EEF8(layer, typeRef, sc);
        func_0026EBC0(layer, "type_text_on", ref);
        func_0026EC48(layer, ref, typeRects + 5 * W32(0x27C + 4 * side));
        if (side == 0) {
            func_0026EBC0(layer, "mc_type_plate_turn", ref);
            func_0026EFC8(layer, ref, 16);
        }
        for (m = 0; m < 3; m++) {
            func_0026EBC0(layer, typeNames[m], ref);
            func_0026EC48(layer, ref, typeRects + 5 * m);
            tbl = *(u8 **)(D_0042BB7C + 0x2D8 + 4 * side);
            val = W32(0x29C + 4 * side);
            if (val >= 2) {
                val = 1;
            }
            idx = 2 * side + val;
            r = *(s32 *)(tbl + 44 * (7 * W32(0x24C + 4 * idx) + W32(0x23C + 4 * idx)));
            if (r == 130) {
                if (m == 2) {
                    func_0026EF88(layer, ref, 0x1.999998p-2f);
                }
            } else if (m == 2) {
                func_0026EF88(layer, ref, 1.0f);
            }
        }
    }

    /* colour select */
    for (side = 0; side < 2; side++) {
        layer = D_0042BB7C + 0xD8 + 40 * side;
        lvl = W32(0x294 + 4 * side);
        offX = (lvl < 3) ? 25 : 0;
        offY = (W32(0x294 + 4 * side) < 4) ? 14 : 0;
        func_0026EBC0(layer, "mc_select_color_on", colorRef);
        cur = W32(0x284 + 4 * side);
        func_0026EEC8(layer, colorRef, offX + 50 * (cur % 3), offY + 28 * (cur / 3));
        func_0026EC48(layer, colorRef, colorRects + 5 * W32(0x284 + 4 * side));
        for (m = 0; m < 6;) {
            func_00325830(nameBuf, "mc_select_color_off_%d", m + 1);
            func_0026EBC0(layer, (const char *)nameBuf, colorRef);
            func_0026EC48(layer, colorRef, colorRects + 5 * m);
            func_0026EEC8(layer, colorRef, offX, offY);
            if (m < W32(0x294 + 4 * side)) {
                func_0026EFC8(layer, colorRef, 4);
            } else {
                func_0026EFC8(layer, colorRef, 8);
            }
            if (m == W32(0x284 + 4 * side)) {
                sc = func_0026F148(layer, colorRef);
                func_0026EBC0(layer, "mc_select_color_on", colorRef);
                func_0026EEF8(layer, colorRef, sc);
            }
            m++;
        }
    }

    /* character plates, cursors, buttons */
    for (side = 0; side < 2; side++) {
        layer = D_0042BB7C + 0x88 + 40 * side;
        __builtin_memset(sel, 0, 8);
        func_0026EB20(layer, 0, side ? 362 : 154);
        if ((W32(0x238) & (0x1000 << side)) != 0) {
            sel[side] = 1;
        }
        if ((W32(0x238) & (0x100 << side)) != 0) {
            sel[side] = 2;
        }
        if (W32(0x3740) != 1) {
            if ((W32(0x238) & 0x100) == 0) {
                sel[1] = 2;
            }
        }
        mode = W32(0x3740);
        if (mode == 1) {
            cell = (side != 0);
        } else if (mode == 0) {
            cell = side ? 2 : 0;
        } else if (mode == 2) {
            cell = 2;
        } else {
            cell = 0;
        }
        row = cell >> 1;
        rc[0] = (cell - 2 * row) << 6;
        rc[1] = row * 32;
        rc[2] = rc[0] + 64;
        rc[3] = rc[1] + 32;
        func_0026EBC0(layer, "mc_chara_plate_text", ref);
        func_0026EC48(layer, ref, rc);
        func_0026EBC0(layer, "mc_chara_cursor", ref);
        func_0026EEC8(layer, ref, 60 * W32(0x23C + 4 * (2 * side + W32(0x29C + 4 * side))), 0);
        if (sel[side] == 1) {
            func_0026EFC8(layer, ref, 2);
        } else if (sel[side] == 2) {
            func_0026EFC8(layer, ref, 8);
        } else {
            func_0026EFC8(layer, ref, 5);
        }
        btnRect[0] = 32;
        btnRect[2] = 64;
        btnRect[3] = 32;
        btnRect[1] = 0;
        func_0026EBC0(layer, "mc_r_button", ref);
        func_0026EC48(layer, ref, btnRect);
        func_0026EBC0(layer, "mc_lr_buttonanime", ref);
        func_0026EEC8(layer, ref, 60 * W32(0x23C + 4 * (2 * side + W32(0x29C + 4 * side))), 0);
        if (sel[side] == 1) {
            func_0026EFC8(layer, ref, 2);
        } else if (sel[side] == 2) {
            func_0026EFC8(layer, ref, 8);
        } else {
            tbl = *(u8 **)(D_0042BB7C + 0x2D8 + 4 * side);
            val = W32(0x29C + 4 * side);
            if (val >= 2) {
                val = 1;
            }
            idx = 2 * side + val;
            if (*(s32 *)(tbl + 44 * (7 * W32(0x24C + 4 * idx) + W32(0x23C + 4 * idx)) + 4) != 0) {
                func_0026EFC8(layer, ref, 4);
            } else {
                func_0026EFC8(layer, ref, 8);
            }
            func_0026EFC8(layer, ref, 1);
        }
        func_0026EBC0(layer, "mc_chara_select_yazirushi_anime", ref);
        if (W32(0x3734) < 2) {
            func_0026EFC8(layer, ref, 8);
        } else if (sel[side] == 1) {
            func_0026EFC8(layer, ref, 2);
        } else if (sel[side] == 2) {
            func_0026EFC8(layer, ref, 8);
        } else {
            func_0026EFC8(layer, ref, 5);
        }
        if (W32(0x3734) >= 2) {
            func_0026EBC0(layer, "mc_chara_select_yazurushi_down", ref);
            func_0026EC48(layer, ref, arrowRect);
        }
    }

    for (m = 0; m < 5; m++) {
        r = func_0026EA58(D_0042BB7C + 0x38 + 40 * m);
    }
    return r;
}
