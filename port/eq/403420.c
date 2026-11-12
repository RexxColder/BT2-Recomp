#include "common.h"

/* Menu overlay: builds the option-menu layers (guide eye/mouth, text window, row highlights,
 * per-mode choice lists). state->mode (0x110) selects the list: 0 time, 1/3 level, 2 item, 4 transform. */

extern u8 *D_0042BB70;

s32 func_00277E70(u8 *dst, s32 val, s64 size);
s32 func_0026EBC0(u8 *layer, const char *name, u8 *obj);
void func_002495A8(u8 *layer, u8 *obj, u8 *arg2, s32 arg3);
void func_00249778(u8 *layer, u8 *obj, u8 *arg2, s32 arg3);
void func_00249FB8(u8 *layer, u8 *obj, s32 x, s32 y, s32 w, s32 h, s32 arg6);
void func_0026EEC8(u8 *layer, u8 *obj, s32 x, s32 y);
void func_0026EFC8(u8 *layer, u8 *obj, s32 flags);
void func_0026EEF8(u8 *layer, u8 *obj, f32 scale);
f32 func_0026F148(u8 *layer, u8 *obj);
s32 func_0026EC48(u8 *layer, u8 *obj, s32 *rect);
void func_0026EC78(u8 *layer, u8 *obj, u8 *arg2, u8 *arg3, s32 *rect, s32 arg5, s32 arg6, s32 arg7);
s32 func_0026EA58(u8 *layer);

#define W(p, off) (*(s32 *)((p) + (off)))
#define ST_FLAGS 0x10C
#define ST_MODE 0x110
#define ST_COUNT 0x120
#define ST_CUR 0x11C

s32 func_00403420(void) {
    u8 *state;
    u8 *layer;
    u8 handle[16];
    u8 handle2[16];
    s32 rectA[6];
    s32 rectB[6];
    s32 rectC[6];
    s32 xoff[6] = {0, -2, 7, 14, 28, 0};
    s32 yoff[6] = {0, 34, 67, 104, 138, 209};
    char menu_rows[6][255] = {"mc_menutext_time",   "mc_menutext_level",     "mc_menutext_item",
                              "mc_menutext_referee", "mc_menutext_transform", "mc_menutext_default"};
    char time_rows[5][255] = {"mc_time_60", "mc_time_90", "mc_time_120", "mc_time_150", "mc_time_mugen"};
    char level_rows[6][255] = {"level_menu_off_veryeasy", "level_menu_off_easy", "level_menu_off_normal",
                               "level_menu_off_hard",     "level_menu_off_veryhard", "mc_referee_menu_off_ana3"};
    char item_rows[2][255] = {"item_menu_on", "item_menu_off"};
    char xform_rows1[2][255] = {"mc_transform_menu_on1", "mc_transform_menu_off1"};
    char xform_rows2[2][255] = {"mc_transform_menu_on2", "mc_transform_menu_off2"};
    char hapa_rows[3][255] = {"mc_hapa_anime1", "mc_hapa_anime2", "mc_hapa_anime3"};
    s32 i;
    s32 plr;
    s32 mode;
    s32 mark_x;
    s32 mark_y;
    s32 cur_item;
    s32 ret;

    state = D_0042BB70;
    func_00277E70((u8 *)W(state, 0x60), 0, 0x80);
    layer = state + 0x38;
    func_0026EBC0(layer, "mcGuideEye", handle);
    func_002495A8(layer, handle, state + 0x12C, 1);
    func_0026EBC0(layer, "mcGuideMouth", handle);
    func_00249778(layer, handle, state + 0x130, 3);
    func_0026EBC0(layer, "mc_textwindow", handle);
    func_00249FB8(layer, handle, 0, 0, W(state, 0xC), W(state, 0x114), 0);

    /* highlight of the selected main row */
    func_0026EBC0(layer, "mc_menutext_onanime", handle);
    func_0026EEC8(layer, handle, xoff[W(state, ST_MODE)], yoff[W(state, ST_MODE)]);
    if (W(state, ST_FLAGS) & 4) {
        func_0026EFC8(layer, handle, 2);
        func_0026EEF8(layer, handle, 0x1.B33332p-1f);
    } else {
        func_0026EFC8(layer, handle, 1);
    }

    rectA[0] = 0;
    rectA[1] = 32 * W(state, ST_MODE);
    rectA[2] = 512;
    rectA[3] = 32 * W(state, ST_MODE) + 32;
    rectA[4] = 0;
    func_0026EBC0(layer, "mc_menutext_on", handle);
    func_0026EC48(layer, handle, rectA);

    rectC[0] = 0;
    rectC[1] = 0;
    rectC[2] = 512;
    rectC[3] = 32;
    rectC[4] = 0;
    func_0026EBC0(layer, "mc_menulineanime", handle);
    func_0026EFC8(layer, handle, W(state, ST_MODE) != 5 ? 4 : 8);
    if (!(W(state, ST_FLAGS) & 4)) {
        func_0026EC78(layer, handle, state + 0x138, state + 0x150, rectC, 1, 6, 2);
    }

    rectB[0] = 0;
    rectB[1] = 0;
    rectB[2] = 64;
    rectB[3] = 64;
    rectB[4] = 0;
    func_0026EBC0(layer, "mc_sword", handle);
    if (!(W(state, ST_FLAGS) & 4)) {
        func_0026EC78(layer, handle, state + 0x13C, state + 0x154, rectB, 6, 1, 4);
    }
    func_0026EBC0(layer, "mc_menu_plate_trun", handle);
    func_0026EFC8(layer, handle, 16);

    /* the six main rows */
    rectA[0] = 0;
    rectA[1] = 0;
    rectA[2] = 512;
    rectA[3] = 32;
    rectA[4] = 0;
    for (i = 0; i < 6; i++) {
        rectA[3] = 32 * i + 32;
        rectA[1] = 32 * i;
        func_0026EBC0(layer, menu_rows[i], handle);
        func_0026EC48(layer, handle, rectA);
        if (i == W(D_0042BB70, ST_MODE)) {
            func_0026EFC8(layer, handle, 8);
            if (!(W(D_0042BB70, ST_FLAGS) & 4)) {
                func_0026EBC0(layer, "mc_menutext_onanime", handle2);
                func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
            }
        } else {
            func_0026EFC8(layer, handle, 4);
        }
    }

    func_0026EBC0(layer, "mc_timemenu_onanime", handle);
    func_0026EFC8(layer, handle, 8);
    func_0026EBC0(layer, "level_menu_on_anime", handle);
    func_0026EFC8(layer, handle, 8);
    func_0026EBC0(layer, "mc_gauge_onanime", handle);
    func_0026EFC8(layer, handle, 8);
    func_0026EBC0(layer, "mc_gauge_menu_on_stop", handle);
    func_0026EFC8(layer, handle, 8);
    func_0026EBC0(layer, "mc_item_menu_onon", handle);
    func_0026EFC8(layer, handle, 8);

    mode = W(D_0042BB70, ST_MODE);
    switch (mode) {
    case 0:
        for (i = 0; i < W(D_0042BB70, ST_COUNT); i++) {
            rectB[0] = 64 * i;
            rectB[1] = 0;
            rectB[2] = 64 * i + 64;
            rectB[3] = 32;
            func_0026EBC0(layer, time_rows[i], handle);
            func_0026EC48(layer, handle, rectB);
            if (i == W(D_0042BB70, ST_CUR)) {
                func_0026EBC0(layer, "mc_timemenu_on", handle2);
                func_0026EC48(layer, handle2, rectB);
                func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
            }
        }
        func_0026EBC0(layer, "mc_timemenu_onanime", handle);
        func_0026EFC8(layer, handle, 4);
        func_0026EEC8(layer, handle, 40 * W(D_0042BB70, ST_CUR), 0);
        break;
    case 1:
    case 3:
        for (i = 0; i < W(D_0042BB70, ST_COUNT); i++) {
            rectB[0] = 0;
            rectB[1] = 32 * i;
            rectB[2] = 512;
            rectB[3] = 32 * i + 32;
            func_0026EBC0(layer, level_rows[i], handle);
            func_0026EFC8(layer, handle, 4);
            func_0026EC48(layer, handle, rectB);
            if (i == W(D_0042BB70, ST_CUR)) {
                func_0026EFC8(layer, handle, 8);
                func_0026EBC0(layer, "level_menu_on", handle2);
                func_0026EC48(layer, handle2, rectB);
                func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
            }
        }
        func_0026EBC0(layer, "level_menu_on_anime", handle);
        func_0026EFC8(layer, handle, 4);
        if (W(D_0042BB70, ST_MODE) == 3) {
            func_0026EEC8(layer, handle, -6, 40 * W(D_0042BB70, ST_CUR) - 20);
        } else if (W(D_0042BB70, ST_MODE) == 1) {
            func_0026EEC8(layer, handle, 0, 40 * W(D_0042BB70, ST_CUR));
        }
        break;
    case 2:
        for (i = 0; i < W(D_0042BB70, ST_COUNT); i++) {
            rectB[0] = 64 * i;
            rectB[1] = 0;
            rectB[2] = 64 * i + 64;
            rectB[3] = 32;
            func_0026EBC0(layer, item_rows[i], handle);
            func_0026EC48(layer, handle, rectB);
            if (i == W(D_0042BB70, ST_CUR)) {
                func_0026EBC0(layer, "mc_item_menu_onon", handle2);
                func_0026EC48(layer, handle2, rectB);
                func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
            }
        }
        func_0026EBC0(layer, "mc_item_menu_onon", handle);
        func_0026EFC8(layer, handle, 4);
        func_0026EEC8(layer, handle, 80 * W(D_0042BB70, ST_CUR), 0);
        break;
    case 4:
        plr = 0;
        mark_x = 0;
        mark_y = 0;
        cur_item = W(D_0042BB70, W(D_0042BB70, 0x118) == 2 ? 0x16C + 8 : 0x168 + 8);
        do {
            for (i = 0; i < W(D_0042BB70, ST_COUNT); i++) {
                rectB[0] = 64 * i;
                rectB[1] = 0;
                rectB[2] = 64 * i + 64;
                rectB[3] = 32;
                func_0026EBC0(layer, plr ? xform_rows2[i] : xform_rows1[i], handle);
                func_0026EC48(layer, handle, rectB);
                if (i == W(D_0042BB70, ST_CUR) && plr == W(D_0042BB70, 0x118) - 2) {
                    func_0026EBC0(layer, "mc_transform_menu_on", handle2);
                    func_0026EC48(layer, handle2, rectB);
                    func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
                }
                if (i == cur_item && plr != W(D_0042BB70, 0x118) - 2) {
                    func_0026EBC0(layer, "mc_item_menu_on_stop", handle2);
                    func_0026EC48(layer, handle2, rectB);
                    func_0026EEF8(layer, handle2, func_0026F148(layer, handle));
                }
            }
            if (plr == W(D_0042BB70, 0x118) - 2) {
                func_0026EBC0(layer, "mc_transform_menu_on", handle);
                func_0026EFC8(layer, handle, 4);
                func_0026EEC8(layer, handle, 80 * W(D_0042BB70, ST_CUR), mark_y);
            } else {
                func_0026EBC0(layer, "mc_item_menu_on_stop", handle);
                func_0026EFC8(layer, handle, 4);
                func_0026EEC8(layer, handle, 16 * (5 * cur_item), mark_x);
            }
            rectB[0] = 0;
            rectB[1] = 64 * plr;
            rectB[2] = 128;
            rectB[3] = 64 * plr + 64;
            func_0026EBC0(layer, plr ? "mc_gaugeplayer_2p" : "mc_gaugeplayer_1p", handle);
            plr++;
            mark_x += 73;
            func_0026EC48(layer, handle, rectB);
            mark_y += 73;
        } while (plr < 2);
        break;
    default:
        break;
    }

    /* hapa (button hint) animations on the second layer */
    layer = D_0042BB70 + 0x10;
    rectB[0] = 0;
    rectB[1] = 0;
    rectB[2] = 64;
    rectB[3] = 64;
    rectB[4] = 0;
    for (i = 0; i < 3; i++) {
        func_0026EBC0(layer, hapa_rows[i], handle);
        func_0026EC78(layer, handle, D_0042BB70 + 0x140 + 4 * i, D_0042BB70 + 0x158 + 4 * i, rectB, 6, 1, 4);
    }

    i = 0;
    plr = 1;
    do {
        plr--;
        ret = func_0026EA58(D_0042BB70 + i + 0x10);
        i += 0x28;
    } while (plr >= 0);
    return ret;
}
