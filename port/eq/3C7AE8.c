#include "common.h"

extern u8 *D_00423114;  /* character-select UI state */
extern char D_00423268[3][255];  /* type text object names */
extern s32 D_004235A8[6][5] __attribute__((aligned(4)));     /* colour-swatch rects */
extern s32 D_004236C0[5];        /* arrow rect */

s32 func_00277E70(u8 *a0, s32 a1, s64 a2);
s32 func_0026EBC0(u8 *layer, const char *name, u8 *obj);
s32 func_0026EC48(u8 *layer, u8 *obj, u8 *rect);
s32 func_0026EEC8(u8 *layer, u8 *obj, s32 x, s32 y);
s32 func_0026EEF8(u8 *layer, u8 *obj, f32 f);
s32 func_0026EF88(u8 *layer, u8 *obj, f32 f);
f32 func_0026F148(u8 *layer, u8 *obj);
s32 func_0026EFC8(u8 *layer, u8 *obj, s32 v);
s32 func_00249BB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_00249DB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_0024A598(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_0024B6C8(s32 id);
s32 func_00325830(u8 *buf, const char *fmt, ...);
s32 func_0026EB20(u8 *layer, s32 x, s32 y);
s32 func_0026EA58(u8 *layer);

#define MENU            (D_00423114)
#define MENU_S32(off)   (*(s32 *)(MENU + (off)))
#define MENU_F32(off)   (*(f32 *)(MENU + (off)))
#define CUR             MENU_S32(0x188)                      /* current player */
#define PSLOT(off)      (*(s32 *)(MENU + (off) + 4 * CUR))   /* per-player slot */
#define FLAGS           MENU_S32(0x18C)
#define COUNT           MENU_S32(0x3644)
/* character entry of the current player (44 bytes each) */
#define ENTRY()         (*(u8 **)(MENU + 0x1CC + 4 * CUR) + 44 * (7 * PSLOT(0x198) + PSLOT(0x190)))

void func_003C7AE8(void) {
    u8 sp[0x20];                 /* object handle at +0, rect at +0x10 */
    s32 *rect = (s32 *)(sp + 0x10);
    u8 *layer;
    char buf[0x120];
    char names[3][255];
    u8 objName[0x20];
    u8 objColor[0x20];
    s32 rect2[4];
    s32 rect3[5];
    s32 selRects[6][5];
    s32 offX;
    s32 offY;
    s32 i;
    s32 id;
    s32 mode;
    s32 n;
    f32 f;

    func_00277E70(*(u8 **)(MENU + 0xC0), 0, 0x80);
    layer = MENU + 0x48;
    if (FLAGS & 0x40) {
        MENU_F32(0x3630) = MENU_F32(0x3630) + 0.075f;
        if (1.0f <= MENU_F32(0x3630)) {
            MENU_F32(0x3630) = 1.0f;
        }
    } else {
        MENU_S32(0x3630) = 0;
    }
    func_0026EBC0(layer, "mc_single_chara_l", sp);
    func_0026EEF8(layer, sp, MENU_F32(0x3630));

    if ((FLAGS & 0x20000000) && CUR != 0) {
        func_0026EBC0(layer, "mc_entry_dummy_text", sp);
        func_0024A598(layer, sp, 0, 0, MENU_S32(0x1C), 44, 1);
    }

    id = *(s32 *)ENTRY();
    if (7 * PSLOT(0x198) + PSLOT(0x190) >= 74) {
        id = 132;
    }
    func_0026EBC0(layer, "mc_name_text_r", sp);
    func_00249BB8(layer, sp, 0, 0, MENU_S32(0x14), id, 2);
    func_0026EBC0(layer, "mc_form_text_r", sp);
    func_00249DB8(layer, sp, 0, 0, MENU_S32(0x18), id, 2);

    func_0026EBC0(layer, "mc_chara_entry", sp);
    if (FLAGS & 0x100) {
        func_0026EFC8(layer, sp, 8);
    } else {
        rect[1] = (COUNT / 4) << 6;
        rect[3] = rect[1] + 0x40;
        rect[0] = (COUNT % 4) << 6;
        rect[2] = rect[0] + 0x40;
        func_0026EEC8(layer, sp, 60 * (COUNT % 4), (COUNT / 4) << 6);
        func_0026EC48(layer, sp, sp + 0x10);
        func_0026EFC8(layer, sp, 4);
    }

    for (i = 0; i < 8; i++) {
        rect[3] = (i / 4) * 32 + 0x20;
        rect[0] = (i % 4) << 6;
        rect[1] = (i / 4) * 32;
        rect[2] = rect[0] + 0x40;
        func_00325830((u8 *)buf, "mc_entry_decision_text%d", i);
        func_0026EBC0(layer, buf, sp);
        func_0026EC48(layer, sp, sp + 0x10);
        func_0026EFC8(layer, sp, i < COUNT ? 4 : 8);
    }
    for (i = 0; i < 8; i++) {
        func_00325830((u8 *)buf, "mc_chara_entry_00%d", i);
        func_0026EBC0(layer, buf, sp);
        func_0026EFC8(layer, sp, i < COUNT ? 4 : 8);
    }

    func_0026EBC0(layer, "mc_entry_change_g", sp);
    func_0026EFC8(layer, sp, (FLAGS & 0x20000000) ? 4 : 8);
    func_0026EBC0(layer, "mc_name_plate_turn", sp);
    func_0026EFC8(layer, sp, 0x10);

    /* type text */
    layer = MENU + 0x98;
    func_0026EB20(layer, 0, 0xA6);
    __builtin_memcpy(names, D_00423268, sizeof(names));
    func_0026EBC0(layer, "mc_type_text_onanime", objName);
    func_0026EEC8(layer, objName, 0, 22 * PSLOT(0x1A8));
    func_0026EBC0(layer, names[PSLOT(0x1A8)], sp);
    f = func_0026F148(layer, sp);
    func_0026EEF8(layer, objName, f);
    rect2[2] = 0x100;
    rect2[0] = 0;
    rect2[1] = PSLOT(0x1A8) << 5;
    rect2[3] = rect2[1] + 0x20;
    func_0026EBC0(layer, "type_text_on", sp);
    func_0026EC48(layer, sp, (u8 *)rect2);
    func_0026EBC0(layer, "mc_type_plate_turn", sp);
    func_0026EFC8(layer, sp, 0x10);

    for (i = 0; i < 3; i++) {
        rect2[1] = i << 5;
        rect2[3] = rect2[1] + 0x20;
        rect2[2] = 0x100;
        rect2[0] = 0;
        func_0026EBC0(layer, names[i], sp);
        func_0026EC48(layer, sp, (u8 *)rect2);
        if (i == 2) {
            func_0026EF88(layer, sp, *(s32 *)ENTRY() == 0x82 ? 0.4f : 1.0f);
        }
    }

    /* colour swatches */
    __builtin_memcpy(selRects, D_004235A8, sizeof(selRects));
    offX = func_0024B6C8(*(s32 *)ENTRY()) < 3 ? 25 : 0;
    offY = func_0024B6C8(*(s32 *)ENTRY()) < 4 ? 14 : 0;
    func_0026EBC0(layer, "mc_select_color_on", objColor);
    func_0026EEC8(layer, objColor, offX + 50 * (PSLOT(0x1B0) % 3), offY + 28 * (PSLOT(0x1B0) / 3));
    func_0026EC48(layer, objColor, (u8 *)selRects[PSLOT(0x1B0)]);
    for (i = 0; i < 6; i++) {
        func_00325830((u8 *)buf, "mc_select_color_off_%d", i + 1);
        func_0026EBC0(layer, buf, objColor);
        func_0026EC48(layer, objColor, (u8 *)selRects[i]);
        func_0026EEC8(layer, objColor, offX, offY);
        func_0026EFC8(layer, objColor, i < func_0024B6C8(*(s32 *)ENTRY()) ? 4 : 8);
        if (i == PSLOT(0x1B0)) {
            f = func_0026F148(layer, objColor);
            func_0026EBC0(layer, "mc_select_color_on", objColor);
            func_0026EEF8(layer, objColor, f);
        }
    }

    /* plate, cursor and arrows */
    layer = MENU + 0x70;
    func_0026EB20(layer, 0, 0x18);
    mode = (FLAGS & 0x1000) != 0;
    if (FLAGS & 0x100) {
        mode = 2;
        n = COUNT - 1;
    } else {
        n = COUNT;
    }
    rect3[1] = (n / 2) << 5;
    rect3[3] = rect3[1] + 0x20;
    rect3[0] = (n % 2) << 6;
    rect3[2] = rect3[0] + 0x40;
    func_0026EBC0(layer, "mc_chara_plate_text", sp);
    func_0026EC48(layer, sp, (u8 *)rect3);

    func_0026EBC0(layer, "mc_chara_cursor", sp);
    func_0026EEC8(layer, sp, 60 * PSLOT(0x190), 0);
    if (mode == 1) {
        func_0026EFC8(layer, sp, 2);
    } else if (mode == 2) {
        func_0026EFC8(layer, sp, 8);
    } else {
        func_0026EFC8(layer, sp, 5);
    }

    rect3[0] = 0x20;
    rect3[2] = 0x40;
    rect3[3] = 0x20;
    rect3[1] = 0;
    func_0026EBC0(layer, "mc_r_button", sp);
    func_0026EC48(layer, sp, (u8 *)rect3);

    func_0026EBC0(layer, "mc_lr_buttonanime", sp);
    func_0026EEC8(layer, sp, 60 * PSLOT(0x190), 0);
    if (mode == 1) {
        func_0026EFC8(layer, sp, 2);
    } else if (mode == 2) {
        func_0026EFC8(layer, sp, 8);
    } else {
        if (*(s32 *)(ENTRY() + 4) != 0) {
            func_0026EFC8(layer, sp, 4);
        } else {
            func_0026EFC8(layer, sp, 8);
        }
        func_0026EFC8(layer, sp, 1);
    }

    func_0026EBC0(layer, "mc_chara_select_yazirushi_anime", sp);
    if (MENU_S32(0x3628) < 2) {
        func_0026EFC8(layer, sp, 8);
    } else if (mode == 1) {
        func_0026EFC8(layer, sp, 2);
    } else if (mode == 2) {
        func_0026EFC8(layer, sp, 8);
    } else {
        func_0026EFC8(layer, sp, 5);
    }
    if (MENU_S32(0x3628) >= 2) {
        __builtin_memcpy(rect3, D_004236C0, 20);
        func_0026EBC0(layer, "mc_chara_select_yazurushi_down", sp);
        func_0026EC48(layer, sp, (u8 *)rect3);
    }

    for (i = 0; i < 4; i++) {
        func_0026EA58(MENU + 0x20 + 0x28 * i);
    }
}
