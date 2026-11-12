#include "common.h"

/* Menu overlay: tournament / game-mode select screen, draws the Flash layers each frame. */
extern u8 *D_00423118;  /* menu object */
extern u8 *D_00387F2C;  /* save data buffer */
extern s32 D_003B0D84 __attribute__((section(".data")));

void func_0026EBC0(u8 *layer, const char *name, u8 *ref);
void func_0026EC48(u8 *layer, u8 *ref, s32 *rect);
void func_0026EFC8(u8 *layer, u8 *ref, s32 prop);
void func_0026EEF8(u8 *layer, u8 *ref, f32 f12);
void func_0026EEC8(u8 *layer, u8 *ref, s32 x, s32 y);
f32 func_0026F148(u8 *layer, u8 *ref);
void func_0026ED60(u8 *layer, u8 *ref, s32 *rect, f32 *a3, f32 *a4, f32 f12, f32 f13);
s32 func_0026EA58(u8 *layer);
void func_002495A8(u8 *layer, u8 *ref, u8 *a2, s32 a3);
void func_00249778(u8 *layer, u8 *ref, u8 *a2, s32 a3);
void func_00249FB8(u8 *layer, u8 *ref, s32 a2, s32 a3, u8 *a4, s32 a5, s32 a6);
void func_00249A98(u8 *layer, u8 *ref, s32 a2, s32 a3, s32 a4, s32 a5);
s32 func_0028C4B8(s32 a0);
s32 func_0024C060(void);

#define W32(off) (*(s32 *)(D_00423118 + (off)))
#define FLAGS    W32(0x134)  /* unlocked / state bits */
#define MODE     W32(0x138)  /* selected game mode */
#define LEVEL    W32(0x13C)  /* selected difficulty */
#define PEOPLE   W32(0x140)  /* player count */

s32 func_003CBE58(void) {
    /* names of the Flash objects, 255 bytes each */
    char modeNames[3][255] = {"mc_tenkaiti", "mc_cellgame", "mc_tenkaiti_dai"};
    char imageNames[3][255] = {"mc_image_t", "mc_image_c", "mc_image_t_d"};
    char clearNames[4][255] = {"mc_clear_mark_1", "mc_clear_mark_2", "mc_clear_mark_3",
                               "mc_clear_mark_4"};
    char levelNames[4][255] = {"mc_syokyuu_t", "mc_tyuukyuu_t", "mc_joukyuu_t", "mc_tyoukyuu_t"};
    char pictureNames[3][255] = {"mc_record_picture_0", "mc_record_picture_1",
                                 "mc_record_picture_2"};
    char numberNames[3][255] = {"mc_record_number_0", "mc_record_number_1", "mc_record_number_2"};
    u8 ref[16];
    u8 ref2[16];
    s32 rc[8];  /* x0, y0, x1, y1 */
    u8 *ui;
    s32 i;
    s32 v;
    s32 row;
    s32 col;
    f32 sc;

    ui = D_00423118 + 0x88;

    func_0026EBC0(ui, "mc_Guide_Eye", ref);
    func_002495A8(ui, ref, D_00423118 + 0x160, 1);
    func_0026EBC0(ui, "mc_Guide_Mouth", ref);
    func_00249778(ui, ref, D_00423118 + 0x164, 3);
    func_0026EBC0(ui, "mc_textwindow", ref);
    func_00249FB8(ui, ref, 0, 0, *(u8 **)(D_00423118 + 0xC), W32(0x144), 1);

    /* mode labels */
    for (i = 0; i < 3;) {
        func_0026EBC0(ui, modeNames[i], ref);
        if ((FLAGS & (0x10 << i)) != 0) {
            rc[3] = 32 * i + 32;
            rc[1] = 32 * i;
        } else {
            rc[1] = 96;
            rc[3] = 128;
        }
        rc[0] = 0;
        rc[2] = 256;
        func_0026EC48(ui, ref, rc);
        if (i == MODE) {
            i++;
            func_0026EFC8(ui, ref, 8);
            func_0026EBC0(ui, "mc_som_moji_on", ref2);
            sc = func_0026F148(ui, ref);
            func_0026EEF8(ui, ref2, sc);
        } else {
            func_0026EFC8(ui, ref, 4);
            i++;
        }
    }

    /* mode images */
    for (i = 0; i < 3; i++) {
        func_0026EBC0(ui, imageNames[i], ref);
        row = (i / 2) << 6;
        col = (i % 2) << 7;
        if ((FLAGS & (0x10 << i)) != 0) {
            rc[3] = row + 64;
            rc[2] = col + 128;
            rc[1] = row;
            rc[0] = col;
        } else {
            rc[1] = 64;
            rc[3] = 128;
            rc[0] = 128;
            rc[2] = 256;
        }
        func_0026EC48(ui, ref, rc);
    }

    rc[2] = 256;
    rc[0] = 0;
    rc[1] = 32 * MODE;
    rc[3] = 32 * MODE + 32;
    func_0026EBC0(ui, "mc_com_moji_on", ref);
    func_0026EC48(ui, ref, rc);
    func_0026EBC0(ui, "mc_som_moji_on", ref);
    func_0026EEC8(ui, ref, 0, 60 * MODE);
    if ((FLAGS & 4) != 0) {
        func_0026EFC8(ui, ref, 8);
    } else {
        func_0026EFC8(ui, ref, 4);
    }
    rc[1] = (MODE / 2) << 6;
    rc[3] = rc[1] + 64;
    rc[0] = (MODE % 2) << 7;
    rc[2] = rc[0] + 128;
    func_0026EBC0(ui, "mc_image_select", ref);
    func_0026EC48(ui, ref, rc);
    rc[2] = 256;
    rc[1] = 32 * MODE;
    rc[3] = 32 * MODE + 32;
    rc[0] = 0;
    func_0026EBC0(ui, "mc_select_text", ref);
    func_0026EC48(ui, ref, rc);

    /* clear marks of the selected mode */
    for (i = 0; i < 4;) {
        func_0026EBC0(ui, clearNames[i], ref);
        v = *(s32 *)(D_00387F2C + 0x408) & (1 << (4 * MODE + i));
        i++;
        if (v != 0) {
            func_0026EFC8(ui, ref, 4);
        } else {
            func_0026EFC8(ui, ref, 8);
        }
    }

    /* difficulty plates */
    for (i = 0; i < 4;) {
        if ((FLAGS & (0x400 << i)) != 0) {
            rc[0] = 0;
            rc[1] = 32 * i;
            rc[3] = 32 * i + 32;
            rc[2] = 256;
        } else {
            rc[0] = 0;
            rc[1] = 128;
            rc[3] = 160;
            rc[2] = 256;
        }
        func_0026EBC0(ui, levelNames[i], ref);
        func_0026EC48(ui, ref, rc);
        if (i == LEVEL) {
            i++;
            func_0026EFC8(ui, ref, 8);
            func_0026EBC0(ui, "mc_kaiq_plate_on", ref2);
            sc = func_0026F148(ui, ref);
            func_0026EEF8(ui, ref2, sc);
        } else {
            func_0026EFC8(ui, ref, 4);
            i++;
        }
    }

    rc[0] = 0;
    rc[2] = 256;
    rc[1] = 32 * LEVEL;
    rc[3] = 32 * LEVEL + 32;
    func_0026EBC0(ui, "mc_kaiq_on", ref);
    func_0026EC48(ui, ref, rc);
    func_0026EBC0(ui, "mc_kaiq_plate_on", ref);
    func_0026EEC8(ui, ref, 17 * LEVEL, 33 * LEVEL);
    v = LEVEL;
    rc[2] = 256;
    if (v >= 3) {
        v = 2;
    }
    rc[0] = 0;
    rc[1] = 32 * v;
    rc[3] = 32 * v + 32;
    func_0026EBC0(ui, "mc_kaisen_t", ref);
    func_0026EC48(ui, ref, rc);

    /* arrows */
    if (D_003B0D84 != 1 || func_0028C4B8(1) != 0) {
        func_0026EBC0(ui, "mc_yazirusi_anime", ref);
        func_0026EFC8(ui, ref, 8);
        PEOPLE = 1;
    } else {
        func_0026EBC0(ui, "mc_yazirusi_anime", ref);
        if ((FLAGS & 0x8000) != 0) {
            func_0026EFC8(ui, ref, 8);
        } else {
            func_0026EFC8(ui, ref, 4);
        }
        func_0026EEC8(ui, ref, W32(0x16C), 0);
        rc[2] = 64;
        rc[0] = 32;
        rc[1] = 0;
        rc[3] = 32;
        func_0026EBC0(ui, "mc_yazirusi_l", ref);
        func_0026EC48(ui, ref, rc);
        func_0026EEC8(ui, ref, -2 * W32(0x16C), 0);
    }

    /* player count icon */
    rc[1] = 32 * ((PEOPLE - 1) / 4);
    rc[3] = rc[1] + 32;
    rc[0] = 32 * ((PEOPLE - 1) % 4);
    rc[2] = rc[0] + 32;
    func_0026EBC0(ui, "mc_ninnzuu", ref);
    func_0026EC48(ui, ref, rc);
    func_0026EEC8(ui, ref, W32(0x168), 0);

    rc[3] = 64;
    rc[2] = 512;
    rc[1] = 32;
    rc[0] = 0;
    func_0026EBC0(ui, "mc_tornamentrecord", ref);
    func_0026EC48(ui, ref, rc);

    for (i = 0; i < 3; i++) {
        rc[3] = 32 * i + 32;
        rc[1] = 32 * i;
        rc[0] = 0;
        rc[2] = 256;
        func_0026EBC0(ui, pictureNames[i], ref);
        func_0026EC48(ui, ref, rc);
    }
    rc[1] = 32;
    rc[3] = 64;
    rc[2] = 128;
    rc[0] = 0;
    func_0026EBC0(ui, "mc_record_text_3", ref);
    func_0026EC48(ui, ref, rc);

    /* record numbers of the selected mode */
    for (i = 0; i < 3; i++) {
        func_0026EBC0(ui, numberNames[i], ref);
        if (i == 0) {
            func_00249A98(ui, ref, 22, 2, *(u16 *)(D_00423118 + 0x174 + 2 * MODE), 2);
        } else if (i == 1) {
            func_00249A98(ui, ref, 22, 2, *(u16 *)(D_00423118 + 0x17A + 2 * MODE), 2);
        } else {
            func_00249A98(ui, ref, 22, 2, *(s32 *)(D_00423118 + 0x180 + 4 * MODE), 2);
        }
    }

    /* background */
    ui = D_00423118 + 0x10;
    rc[3] = 256;
    rc[2] = 512;
    rc[1] = 0;
    rc[0] = 0;
    func_0026EBC0(ui, "mc_bg", ref);
    func_0026ED60(ui, ref, rc, (f32 *)(D_00423118 + 0x15C), 0, -0.25f, 0.0f);
    for (i = 0; i < 4; i++) { /* asm 0x3CCE04: li s1,3 + bgezl s1 -> 4 passes (was 3: layer G+0x88 = text window, Android 18, menu never drawn) */
        func_0026EA58(D_00423118 + 0x10 + 40 * i);
    }
    return func_0024C060();
}
