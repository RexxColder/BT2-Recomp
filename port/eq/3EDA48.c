#include "common.h"

/* Training-menu screen refresh (mc_training_*). G = D_00428F4C is the screen state block; layers G+0xA0, G+0x78
 * and G+0x50 are driven by script-node names, the four layers at G+0x28*(k+1) are run at the end. */
extern u8 *D_00428F4C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));    /* save data block */

extern char D_00429B20[];                                    /* mc_textwindow */
extern char D_00429B30[], D_00429B40[], D_00429B50[];        /* mc_training_r / mc_training_s / mc_text_on */
extern char D_00429B60[], D_00429B78[], D_00429B90[];        /* mc_button_icon_next / _mode / _change */
extern char D_00429BA8[];                                    /* mc_item_name */
extern char D_00429BB8[], D_00429BD0[];                      /* mc_yazirusi_down / mc_yazirusi_up */
extern char D_00429BE0[], D_00429BF0[];                      /* mc_yazirusi_r / mc_yazirusi_l */
extern char D_00429C00[];                                    /* mc_training_main_text */
extern char D_00429C18[], D_00429CF0[], D_00429DB0[];        /* 3 x 64 node names each (menu text / plates / marks) */
extern char D_00429CD8[];                                    /* mc_training_plate_on */
extern char D_00429E70[], D_00429E88[];                      /* mc_explanation_text / mc_button_icon_next2 area */
extern char D_00429EA0[], D_00429EB8[];                      /* mc_explanation_screenshot / mc_Guide_eye_v */
extern char D_00429ED8[];                                    /* 8 x 64 node names (menu plates, explanation) */

void func_277E70(u8 *arg0, s32 arg1, s32 arg2);
void func_26EBC0(u8 *layer, char *name, void *handle);
void func_26EC48(u8 *layer, void *handle, void *rect);
void func_26EFC8(u8 *layer, void *handle, s32 flags);
f32 func_26F148(u8 *layer, void *handle);
void func_26EEF8(u8 *layer, void *handle, f32 value);
void func_26EEC8(u8 *layer, void *handle, s32 x, s32 y);
void func_26EA58(u8 *layer);
void func_249FB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_24A598(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_2495A8(u8 *layer, void *handle, u8 *arg2, s32 arg3);
void func_249778(u8 *layer, void *handle, u8 *arg2, s32 arg3);
void func_2498D8(u8 *layer, void *handle, s32 arg2);
void func_003EC910(u8 *layer, void *handle, s32 arg2, s32 arg3);
void func_003ECB28(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 func_2A0EA8(s32 arg0);
void func_24C060(void);

#define G_S32(off) (*(s32 *)(D_00428F4C + (off)))
#define G_U32(off) (*(u32 *)(D_00428F4C + (off)))
#define G_F32(off) (*(f32 *)(D_00428F4C + (off)))

/* 8-byte records of the current menu: [0] = kind, [1] = item count */
#define MENU_REC() ((s32 *)(G_S32(0x184) * 8 + G_S32(0x1AC)))

static void SetRect(s32 *rect, s32 x0, s32 y0, s32 x1, s32 y1) {
    rect[0] = x0;
    rect[1] = y0;
    rect[2] = x1;
    rect[3] = y1;
}

/* the 17 text-row offsets (jump table), indexed by category + selected item */
static s32 TextRowFor(s32 idx) {
    switch (idx) {
    case 0: return 0x5A;
    case 1: return 0x32;
    case 2: return 0x35;
    case 3: return 0x3B;
    case 4: return 0x41;
    case 5: return 0x45;
    case 6: return 1;
    case 7: return 0x2F;
    case 8: return 0x49;
    case 9: return 0x23;
    case 10: return 0x18;
    case 11: return 0x1B;
    case 12: return 8;
    case 13: return 0x13;
    case 14: return 0x28;
    case 15: return 0xF;
    case 16: return 3;
    }
    return 0;
}

void func_003EDA48(void) {
    u8 handle[16];
    s32 rect[4];
    u8 handle2[16];
    char names3[3][64];
    char names4[3][64];
    char names5[3][64];
    char names6[8][64];
    u8 *layer;
    s32 i, j;
    s32 row;
    s32 textRow = 0;
    s32 frames = 0;
    s32 lastKind = 0;
    f32 fade;

    func_277E70(*(u8 **)(D_00428F4C + 0xC8), 0, 0x80);
    layer = D_00428F4C + 0xA0;
    func_26EBC0(layer, D_00429B20, handle);
    func_249FB8(layer, handle, 0, 0, G_S32(8), G_S32(0x17C), 1);

    /* mode tabs: the selected one (G+0x178) is highlighted and gets a text pulse */
    for (i = 0; i < 2; i++) {
        SetRect(rect, 0, i * 32, 0x100, i * 32 + 0x20);
        func_26EBC0(layer, i != 0 ? D_00429B30 : D_00429B40, handle);
        func_26EC48(layer, handle, rect);
        if (i == G_S32(0x178)) {
            func_26EFC8(layer, handle, 8);
            func_26EBC0(layer, D_00429B50, handle2);
            fade = func_26F148(layer, handle);
            func_26EEF8(layer, handle2, fade);
        } else {
            func_26EFC8(layer, handle, 4);
        }
    }

    SetRect(rect, 0, G_S32(0x178) << 5, 0x100, (G_S32(0x178) << 5) + 0x20);
    func_26EBC0(layer, D_00429B50, handle);
    func_26EC48(layer, handle, rect);
    row = G_S32(0x178);
    func_26EEC8(layer, handle, row * 46, row * 53);

    func_26EBC0(layer, D_00429B60, handle);
    func_26EEC8(layer, handle, 0, 0);

    if (G_U32(0x174) & 8) {
        SetRect(rect, 0, 0x20, 0x100, 0x40);
    } else {
        SetRect(rect, 0, 0, 0x100, 0x20);
    }
    func_26EC48(layer, handle, rect);
    func_26EBC0(layer, D_00429B78, handle);
    func_26EEC8(layer, handle, 0, 0);

    if (G_S32(0x180) != 0 || (G_U32(0x174) & 8)) {
        func_26EFC8(layer, handle, 8);
    } else {
        SetRect(rect, 0, 0x40, 0x100, 0x60);
        func_26EC48(layer, handle, rect);
        func_26EFC8(layer, handle, 4);
    }
    func_26EBC0(layer, D_00429B90, handle);
    func_26EEC8(layer, handle, 0, 0);

    if (*(s16 *)(D_00387F2C + 0x27FE) <= 0) {
        func_26EFC8(layer, handle, 8);
    } else if (G_U32(0x174) & 8) {
        func_26EFC8(layer, handle, 8);
    } else if (G_S32(0x180) != 0) {
        func_26EFC8(layer, handle, 8);
    } else {
        SetRect(rect, 0, 0x60, 0x100, 0x80);
        func_26EC48(layer, handle, rect);
        func_26EFC8(layer, handle, 4);
    }
    func_26EBC0(layer, D_00429BA8, handle);
    func_24A598(layer, handle, 0, 0, G_S32(0x18), 0x234, 1);

    /* scroll arrows (layer G+0x78) */
    layer = D_00428F4C + 0x78;
    for (i = 0; i < 2; i++) {
        SetRect(rect, 0, i << 5, 0x20, (i << 5) + 0x20);
        func_26EBC0(layer, i != 0 ? D_00429BB8 : D_00429BD0, handle);
        func_26EC48(layer, handle, rect);

        if (i == 0) {
            if (G_S32(0x188) != 0) {
                func_26EFC8(layer, handle, 4);
            } else {
                func_26EFC8(layer, handle, 8);
            }
        } else {
            s32 count = MENU_REC()[1];

            if (count < 4 || G_S32(0x188) == count - 3) {
                func_26EFC8(layer, handle, 8);
            } else {
                func_26EFC8(layer, handle, 4);
            }
        }

        SetRect(rect, 0x20, i << 5, 0x40, (i << 5) + 0x20);
        func_26EBC0(layer, i != 0 ? D_00429BE0 : D_00429BF0, handle);
        func_26EC48(layer, handle, rect);
        if (i != 0) {
            func_26EFC8(layer, handle, G_S32(0x184) > 0 ? 8 : 4);
        } else {
            func_26EFC8(layer, handle, G_S32(0x184) > 0 ? 4 : 8);
        }
    }

    func_26EBC0(layer, D_00429C00, handle);
    {
        s32 *rec = MENU_REC();

        func_24A598(layer, handle, 0, 0, G_S32(0x10), rec[0] + 0x16, 1);
    }

    /* menu text rows */
    __builtin_memcpy(names3, D_00429C18, 0xC0);
    for (j = 0; j < 3; j++) {
        s32 *rec;

        func_26EBC0(layer, names3[j], handle);
        rec = MENU_REC();
        if (j < rec[1]) {
            s32 kind = rec[0];

            if (kind == 0) {
                lastKind = 1;
            } else if (kind == 1) {
                lastKind = 0x19;
            }
            func_003EC910(layer, handle, lastKind + G_S32(0x188) + j, 1);
        }
        if (G_S32(0x18C) == j) {
            func_26EBC0(layer, D_00429CD8, handle2);
            fade = func_26F148(layer, handle);
            func_26EEF8(layer, handle2, fade);
        }
    }
    func_26EBC0(layer, D_00429CD8, handle);
    func_26EEC8(layer, handle, 0, G_S32(0x18C) * 60);

    /* plates of the visible rows: lit for rows that exist */
    __builtin_memcpy(names4, D_00429CF0, 0xC0);
    for (j = 0; j < 3; j++) {
        s32 *rec;

        func_26EBC0(layer, names4[j], handle);
        rec = MENU_REC();
        if (j < rec[1]) {
            func_26EFC8(layer, handle, 4);
        } else {
            func_26EFC8(layer, handle, 8);
        }
    }

    /* clear marks: set when the matching bit of the save block is set */
    __builtin_memcpy(names5, D_00429DB0, 0xC0);
    for (j = 0; j < 3; j++) {
        s32 *rec;

        func_26EBC0(layer, names5[j], handle);
        rec = MENU_REC();
        if (rec[0] > 0) {
            func_26EFC8(layer, handle, 8);
        } else if (*(u32 *)(D_00387F2C + 0x608) & (1 << (G_S32(0x188) + j))) {
            func_26EFC8(layer, handle, 4);
        } else {
            func_26EFC8(layer, handle, 8);
        }
    }

    /* explanation text / screenshot of the selected entry (menu kind 1) */
    if (MENU_REC()[0] == 1) {
        s32 pick;
        s32 ret;
        u32 *entry;
        s32 *list;

        func_26EBC0(layer, D_00429E70, handle);
        func_003EC910(layer, handle, G_S32(0x188) + G_S32(0x18C) + 0x19, 1);

        textRow = 0;
        frames = 0;
        pick = G_S32(0x188) + G_S32(0x18C);
        if ((u32)pick < 0x11) {
            textRow = TextRowFor(pick);
        }

        G_S32(0x1C8) = G_S32(0x1C4) + *(s32 *)(G_S32(0x1C4) + pick * 4) * 4;
        func_26EBC0(layer, D_00429E88, handle);

        list = (s32 *)(G_S32(0x1A4) * 8 + G_S32(0x1C8));
        entry = (u32 *)((textRow + list[0]) * 4 + G_S32(0x14));
        ret = func_2A0EA8(G_S32(0x14) + (*entry & ~3));
        if (ret == 1) {
            frames = 0x1E;
        } else if (ret == 2) {
            frames = 0x16;
        } else if (ret == 3) {
            frames = 0xA;
        }
        func_003ECB28(layer, handle, 0, frames, G_S32(0x14),
                      textRow + *(s32 *)(G_S32(0x1A4) * 8 + G_S32(0x1C8)), 1, G_S32(0xD8));

        SetRect(rect, 0, 0x20, 0x100, 0x40);
        func_26EBC0(layer, D_00429EA0, handle);
        func_26EC48(layer, handle, rect);
        func_26EBC0(layer, D_00429EB8, handle);
        func_26EEF8(layer, handle, G_F32(0x1F0));
    }

    /* four option cells (layer G+0x50): each has a text and a selection overlay */
    layer = D_00428F4C + 0x50;
    __builtin_memcpy(names6, D_00429ED8, 0x200);
    for (j = 0; j < 4; j++) {
        func_26EBC0(layer, names6[j * 2], handle);
        func_2495A8(layer, handle, D_00428F4C + j * 4 + 0x1CC, 1);
        func_26EBC0(layer, names6[j * 2 + 1], handle);
        if (G_S32(0x190) == j) {
            func_249778(layer, handle, D_00428F4C + j * 4 + 0x1DC, 3);
        } else {
            func_2498D8(layer, handle, 3);
        }
    }

    /* run the four layers */
    for (j = 0; j < 4; j++) {
        func_26EA58(D_00428F4C + j * 0x28 + 0x28);
    }
    func_24C060();
}
