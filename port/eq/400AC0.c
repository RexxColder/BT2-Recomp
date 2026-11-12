#include "common.h"

extern u8 *D_0042A590;  /* menu UI state */
extern u8 *D_003876A4;  /* player data */

s32 func_00277E70(u8 *a0, s32 a1, s64 a2);
s32 func_0026EBC0(u8 *layer, const char *name, u8 *obj);
s32 func_0026ED60(u8 *layer, u8 *obj, u8 *rect, u8 *p, s32 z, f32 f0, f32 f1);
s32 func_0026EC48(u8 *layer, u8 *obj, u8 *rect);
s32 func_0026EC18(u8 *layer, u8 *obj, s32 frame);
s32 func_0026EEF8(u8 *layer, u8 *obj, f32 f);
s32 func_0026EFC8(u8 *layer, u8 *obj, s32 v);
s32 func_00249BB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_00249DB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
s32 func_0024A8A0(u8 *buf, s32 value, s32 digits);
s32 func_0024AB10(u8 *layer, u8 *objs, s32 a2, s32 a3, s32 font, u8 *digits);
s32 func_00325830(u8 *buf, const char *fmt, ...);
s32 func_0026EB20(u8 *layer, s32 x, s32 y);
s32 func_0026EA58(u8 *layer);

#define UI              (D_0042A590)
#define UI_S32(off)     (*(s32 *)(UI + (off)))
#define PLAYER_IDX      (*(s32 *)(D_003876A4 + 0x64))
/* current stage entry: +8 = count, +12 = kind */
#define ENTRY()         (*(u8 **)(UI + 0x274) + 56 * PLAYER_IDX)
#define ENTRY_COUNT()   (*(s32 *)(ENTRY() + 8))
#define ENTRY_KIND()    (*(s32 *)(ENTRY() + 12))

/* tile tag for a tower slot by parity of its position */
static s32 ParityTag(s32 pos, s32 count) {
    if (count & 1) {
        if (pos & 1) {
            return 0;
        }
        return pos ? 1 : 6;
    }
    if (pos & 1) {
        return 1;
    }
    return pos ? 0 : 5;
}

void func_00400AC0(void) {
    u8 sp[0x100];
    s32 *rect = (s32 *)(sp + 0x10);   /* x0, y0, x1, y1 */
    u8 *layer;
    s32 i;
    s32 id;
    s32 tag;
    s32 pos;
    s32 v;
    f32 f;

    func_00277E70(*(u8 **)(UI + 0x11C), 0, 0x80);
    layer = UI + 0xCC;
    rect[3] = 0x80;
    rect[2] = 0x200;
    rect[1] = 0;
    rect[0] = 0;
    func_0026EBC0(layer, "mc_effect_1", sp);
    func_0026ED60(layer, sp, sp + 0x10, UI + 0x254, 0, 18.0f, 0.0f);
    func_0026EBC0(layer, "fr_effect_2", sp);
    func_0026ED60(layer, sp, sp + 0x10, UI + 0x258, 0, 8.0f, 0.0f);

    for (i = 0; i < 2; i++) {
        f32 *fade = (f32 *)(UI + 0x260 + 4 * i + 4);
        if (UI_S32(0x208) & (0x10 << i)) {
            *fade = *fade + 0.075f;
            if (1.0f <= *fade) {
                *fade = 1.0f;
            }
        } else {
            *(s32 *)fade = 0;
        }
        func_0026EBC0(layer, i ? "mc_tag_chara_r1" : "mc_tag_chara_l1", sp);
        func_0026EEF8(layer, sp, *(f32 *)(UI + 0x260 + 4 * i + 4));
    }

    /* name / form texts */
    if (ENTRY_KIND() == 2 || ENTRY_KIND() == 4) {
        for (i = 0; i < 2; i++) {
            id = *(s32 *)(*(u8 **)(UI + 0x278) + 80 * PLAYER_IDX + 4 * (UI_S32(0x23C) + 10 * i));
            func_0026EBC0(layer, i ? "mc_name_text_l" : "mc_name_text_t", sp);
            func_00249BB8(layer, sp, 0, 0, UI_S32(0x24), id, 0);
            func_0026EBC0(layer, i ? "mc_form_text_l" : "mc_form_text_t", sp);
            func_00249DB8(layer, sp, 0, 0, UI_S32(0x28), id, 0);
        }
    } else {
        id = *(s32 *)(*(u8 **)(UI + 0x278) + 80 * PLAYER_IDX + 4 * UI_S32(0x23C));
        func_0026EBC0(layer, "mc_name_text_t", sp);
        func_00249BB8(layer, sp, 0, 0, UI_S32(0x24), id, 0);
        func_0026EBC0(layer, "mc_form_text_t", sp);
        func_00249DB8(layer, sp, 0, 0, UI_S32(0x28), id, 0);
    }
    func_0026EBC0(layer, "mc_chara_effect_turn", sp);
    func_0026EFC8(layer, sp, 0x20);

    /* course name */
    v = PLAYER_IDX % 8;
    rect[1] = (v % 4) << 6;
    rect[3] = rect[1] + 0x40;
    v = PLAYER_IDX % 8;
    rect[0] = (v / 4) << 8;
    rect[2] = rect[0] + 0x100;
    func_0026EBC0(layer, "mc_couse_name", sp);
    func_0026EC48(layer, sp, sp + 0x10);
    func_0026EC18(layer, sp, PLAYER_IDX / 8);

    /* score digits */
    for (i = 0; i < 7; i++) {
        func_00325830(sp + 0x30, "mc_score_number%d", 7 - i);
        func_0026EBC0(layer, sp + 0x30, sp + 0x50 + 8 * i);
    }
    func_0024A8A0(sp + 0x90, 100 * *(s32 *)(D_003876A4 + 0x60), 7);
    func_0024AB10(layer, sp + 0x50, 0, 0, UI_S32(0x284), sp + 0x90);

    if (ENTRY_KIND() == 1) {
        rect[1] = 32;
        rect[3] = 64;
        rect[0] = 256;
        rect[2] = 512;
    } else {
        rect[2] = 256;
        rect[0] = 0;
        rect[3] = (ENTRY_COUNT() - UI_S32(0x23C)) << 5;
        rect[1] = rect[3] - 32;
    }
    func_0026EBC0(layer, "mc_battle_n", sp);
    func_0026EC48(layer, sp, sp + 0x10);

    pos = 0x80;
    rect[1] = 0;
    rect[3] = 0x80;
    if (ENTRY_KIND() != 2) {
        pos = 0;
    }
    rect[0] = pos;
    rect[2] = pos + 0x80;
    func_0026EBC0(layer, "mc_battle_number0", sp);
    func_0026EC48(layer, sp, sp + 0x10);

    if (ENTRY_KIND() == 1) {
        rect[2] = 0x80;
        rect[3] = 0x100;
        rect[1] = 0x80;
        rect[0] = 0;
    } else if (ENTRY_KIND() == 2 || ENTRY_KIND() == 4) {
        rect[0] = 0x80;
        rect[2] = 0x100;
        rect[1] = 0;
        rect[3] = 0x80;
    } else {
        rect[2] = 0x80;
        rect[1] = 0;
        rect[3] = 0x80;
        rect[0] = 0;
    }
    func_0026EBC0(layer, "mc_battle_number1", sp);
    func_0026EC48(layer, sp, sp + 0x10);

    /* clouds */
    rect[3] = 0x100;
    rect[2] = 0x200;
    rect[1] = 0;
    rect[0] = 0;
    for (i = 0; i < 2; i++) {
        layer = i ? UI + 0xA4 : UI + 0x2C;
        func_0026EBC0(layer, i ? "mc_cloud_1" : "mc_cloud_2", sp);
        func_0026EC18(layer, sp, i ^ 1);
        f = i ? -0.5f : -0.2f;
        func_0026ED60(layer, sp, sp + 0x10, UI + 0x24C + 4 * i, 0, f, 0.0f);
    }

    /* tower tiles 1..3 */
    layer = UI + 0x54;
    for (i = 0; i < 3; i++) {
        s32 count;
        func_00325830(sp + 0xA0, "mc_tower_%d", i + 1);
        func_0026EBC0(layer, sp + 0xA0, sp);
        pos = UI_S32(0x240) + i;
        count = ENTRY_COUNT();
        if (pos < count) {
            if (pos == -1) {
                tag = 2;
            } else {
                tag = ParityTag(pos, count);
            }
        } else if (pos == count + 1) {
            tag = 3;
        } else {
            tag = 4;
        }
        func_0026EC18(layer, sp, tag);
    }

    /* tower tiles 4..5 */
    for (i = 0; i < 2; i++) {
        s32 count = ENTRY_COUNT();
        pos = UI_S32(0x244 + 4 * i);
        if (pos == count + 1) {
            tag = 3;
        } else if (pos == count) {
            tag = 4;
        } else if (pos == -1) {
            tag = 2;
        } else {
            tag = ParityTag(pos, count);
        }
        func_0026EBC0(layer, i ? "mc_tower_5" : "mc_tower_4", sp);
        func_0026EC18(layer, sp, tag);
    }

    /* character plates 1..3 */
    for (i = 0; i < 3; i++) {
        func_00325830(sp + 0xC0, "mc_charaplate_%d", i + 1);
        func_0026EBC0(layer, sp + 0xC0, sp);
        if (UI_S32(0x240) + i < ENTRY_COUNT()) {
            func_0026EFC8(layer, sp, 4);
            if (UI_S32(0x240) == ~i) {
                func_0026EC18(layer, sp, 8);
            } else if (ENTRY_KIND() == 2 || ENTRY_KIND() == 4) {
                func_0026EC18(layer, sp, 6);
            } else {
                func_0026EC18(layer, sp, 7);
            }
        } else {
            func_0026EFC8(layer, sp, 8);
        }
    }

    /* character plate 4 */
    func_0026EBC0(layer, "mc_charaplate_4", sp);
    if (UI_S32(0x244) < ENTRY_COUNT()) {
        func_0026EFC8(layer, sp, 4);
        if (UI_S32(0x244) == -1) {
            func_0026EC18(layer, sp, 8);
        } else if (ENTRY_KIND() == 2 || ENTRY_KIND() == 4) {
            func_0026EC18(layer, sp, 6);
        } else {
            func_0026EC18(layer, sp, 7);
        }
    } else {
        func_0026EFC8(layer, sp, 8);
    }

    /* rank numbers 1..3 */
    for (i = 0; i < 3; i++) {
        func_00325830(sp + 0xE0, "mc_rank_number%d2", i + 1);
        func_0026EBC0(layer, sp + 0xE0, sp);
        pos = UI_S32(0x240) + i;
        if (pos < ENTRY_COUNT() && pos != -1) {
            rect[1] = ((pos + 1) / 5) << 5;
            rect[3] = rect[1] + 0x20;
            rect[0] = ((UI_S32(0x240) + i + 1) % 5) << 4;
            rect[2] = rect[0] + 0x10;
            func_0026EC48(layer, sp, sp + 0x10);
            func_0026EFC8(layer, sp, 4);
        } else {
            func_0026EFC8(layer, sp, 8);
        }
    }

    /* rank number 4 */
    func_0026EBC0(layer, "mc_rank_number42", sp);
    pos = UI_S32(0x244);
    if (pos < ENTRY_COUNT() && pos != -1) {
        rect[1] = ((pos + 1) / 5) << 5;
        rect[3] = rect[1] + 0x20;
        rect[0] = ((UI_S32(0x244) + 1) % 5) << 4;
        rect[2] = rect[0] + 0x10;
        func_0026EC48(layer, sp, sp + 0x10);
        func_0026EFC8(layer, sp, 4);
    } else {
        func_0026EFC8(layer, sp, 8);
    }

    /* big rank number */
    layer = UI + 0x7C;
    func_0026EB20(layer, 0x30, 0xA0);
    rect[1] = ((UI_S32(0x240) + 2) / 5) << 5;
    rect[3] = rect[1] + 0x20;
    rect[0] = ((UI_S32(0x240) + 2) % 5) << 4;
    rect[2] = rect[0] + 0x10;
    func_0026EBC0(layer, "mc_rank_number", sp);
    func_0026EC48(layer, sp, sp + 0x10);

    for (i = 0; i < 6; i++) {
        if (i != 5) {
            func_0026EA58(UI + 0x28 * i + 0x2C);
        }
    }
}
