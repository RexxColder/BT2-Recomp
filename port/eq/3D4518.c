#include "common.h"

/* Tournament / match-card screen refresh. obj = screen object (arg0); D_3876A4 = global game block.
 * obj+0xF8, +0x30, +0x58, +0x80, +0x120, +0x148 are UI layers driven by script-node names. */
extern u8 *D_3876A4 __attribute__((section(".data")));

extern char D_00425F88[], D_00425F98[], D_00425FA8[];      /* mc_GuideEye / mcGuideMouth / mc_textwindow */
extern char D_00425FB8[], D_00425FC8[], D_00425FD0[];      /* mc_kaisu / mc_kaiq / mc_button_icon */
extern char D_00425FE0[], D_00425FF8[];                    /* mc_tournament_frame_%d / mc_tournament_chara%d */
extern char D_00426010[];                                  /* 5 words: scroll arrow rectangle */
extern char D_00426028[], D_00426040[];                    /* mc_scroll_yazirushi / _l */
extern char D_00426058[], D_00426070[];                    /* mc_tournament_frame_0 / _1 */
extern char D_00426088[], D_00426098[];                    /* mc_name_text_l / _r */
extern char D_004260A8[], D_004260B8[];                    /* mc_form_text_l / _r */
extern char D_004260C8[], D_004260E0[];                    /* mc_name_plate_turn / mc_kaisen */
extern char D_004260F0[], D_00426100[];                    /* mc_vs_number_r / _l */
extern char D_00426110[], D_00426128[];                    /* mc_victory_or_defeat_l / _r */

void func_26EBC0(u8 *layer, char *name, void *handle);
void func_26EC48(u8 *layer, void *handle, void *rect);
void func_26EC18(u8 *layer, void *handle, s32 arg2);
void func_26EF88(u8 *layer, void *handle, f32 value);
void func_26EFC8(u8 *layer, void *handle, s32 flags);
void func_26EEC8(u8 *layer, void *handle, s32 x, s32 y);
void func_26EB20(u8 *layer, s32 arg1, s32 arg2);
s32 func_26EB70(u8 *layer);
void func_249948(u8 *layer, void *handle, u8 *arg2, s32 arg3);
void func_2495A8(u8 *layer, void *handle, u8 *arg2, s32 arg3);
void func_249778(u8 *layer, void *handle, u8 *arg2, s32 arg3);
void func_2498D8(u8 *layer, void *handle, s32 arg2);
void func_249FB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_249BB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_249DB8(u8 *layer, void *handle, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_325830(char *buf, char *fmt, s32 arg);
s32 func_003D83D0(u8 *obj);
s32 func_003D8458(u8 *obj);

#define O_S32(off) (*(s32 *)(obj + (off)))
#define O_F32(off) (*(f32 *)(obj + (off)))
#define O_U16(off) (*(u16 *)(obj + (off)))
#define ENTRY(idx) (obj + 0x3330 + (idx) * 0x20)            /* 0x20-byte fighter entries */
#define SEL_TABLE(sel, i) O_U16(0x353E + (sel) * 16 + (i) * 2) /* two entry indices per selection */

struct Frame {
    u8 handle[16];       /* 0x00 */
    s32 rect[4];         /* 0x10 */
    u8 pad_20[16];
    char nameBuf[64];    /* 0x30 */
    s32 tileRectA[4];    /* 0x70 */
    u8 pad_80[16];
    s32 scrollRect[5];   /* 0x90 */
    u8 pad_A4[12];
    s32 tileRectB[4];    /* 0xB0 */
    u8 pad_C0[16];
    s32 tileRectC[4];    /* 0xD0 */
    u8 pad_E0[16];
    s32 rectD[4];        /* 0xF0 */
    u8 pad_100[16];
    s32 rectE[4];        /* 0x110 */
};

/* 4 when 3D83D0 reports a state, else 3 when 3D8458 does, else the stored value at +0x3320 */
static s32 PickKaisenRow(u8 *obj) {
    s32 row;

    if (func_003D83D0(obj)) {
        row = 4;
    } else if (func_003D8458(obj)) {
        row = 3;
    } else {
        row = O_S32(0x3320);
    }
    return row;
}

/* tile-frame icons of both entries of the current selection (layers +0x58 and +0x80) */
static void DrawTileFrames(u8 *obj, u8 *layer, struct Frame *fr, s32 *rect) {
    s32 i;
    s32 sel;

    if (!(func_26EB70(layer) & 1)) {
        return;
    }
    sel = O_S32(0x3324);
    for (i = 0; i < 2; i++) {
        u8 *ent = ENTRY(SEL_TABLE(sel, i));

        if (*(u16 *)(ent + 0xC) & 1) {
            u32 tile = *(u16 *)(ent + 0x12);
            s32 x = (tile & 3) << 6;
            s32 y = (tile >> 2) << 6;

            rect[0] = x;
            rect[1] = y;
            rect[2] = x + 0x40;
            rect[3] = y + 0x40;
            func_26EBC0(layer, i != 0 ? D_00426058 : D_00426070, fr->handle);
            func_26EC18(layer, fr->handle, 1);
            func_26EC48(layer, fr->handle, rect);
            sel = O_S32(0x3324);
        }
    }
    {
        u8 *ent = ENTRY(SEL_TABLE(sel, 0));
        s32 *pos = (s32 *)(O_S32(0x3304) + *(u16 *)(ent + 0x14) * 12);
        s32 scroll = (s32)O_F32(0x3330);

        func_26EB20(layer, pos[1] + scroll, pos[2]);
    }
}

/* name / form text of both sides, the name plate turn and the "kaisen" counter */
static void DrawNamesAndRound(u8 *obj, u8 *layer, struct Frame *fr, s32 *rect) {
    s32 i;
    s32 kaisenRow;

    for (i = 0; i < 2; i++) {
        u8 *ent = ENTRY(SEL_TABLE(O_S32(0x3324), i));
        s32 nameId = *(u16 *)(ent + 0xE);

        if ((u32)(nameId - 0x7A) < 2) {
            nameId = 0x85;
        }
        if (!(*(u16 *)(ent + 0x10) < 0x4A)) {
            nameId = 0x84;
        }
        func_26EBC0(layer, i == 0 ? D_00426098 : D_00426088, fr->handle);
        func_249BB8(layer, fr->handle, 0, 0, O_S32(0x24), nameId, i == 0 ? 2 : 0);
        func_26EBC0(layer, i != 0 ? D_004260A8 : D_004260B8, fr->handle);
        func_249DB8(layer, fr->handle, 0, 0, O_S32(0x28), nameId, i == 0 ? 2 : 0);
    }
    func_26EBC0(layer, D_004260C8, fr->handle);
    func_26EFC8(layer, fr->handle, 0x10);

    kaisenRow = PickKaisenRow(obj);
    rect[0] = 0;
    rect[1] = kaisenRow << 5;
    rect[2] = 0x100;
    rect[3] = (kaisenRow << 5) + 0x20;
    func_26EBC0(layer, D_004260E0, fr->handle);
    func_26EC48(layer, fr->handle, rect);
}

/* "vs" number plates of both sides, sliced from a 5-column sheet */
static void DrawVsNumbers(u8 *obj, u8 *layer, struct Frame *fr, s32 *rect) {
    s32 i;

    for (i = 0; i < 2; i++) {
        u8 *ent = ENTRY(SEL_TABLE(O_S32(0x3324), i));

        if (*(u16 *)(ent + 0xC) & 1) {
            u32 n = *(u16 *)(ent + 0x12);
            u32 col = n % 5;
            u32 row = n / 5;

            rect[1] = row << 6;
            rect[3] = (row << 6) + 0x40;
            rect[0] = col * 96;
            rect[2] = col * 96 + 0x60;
        } else {
            rect[1] = 0x40;
            rect[3] = 0x80;
            rect[0] = 0x120;
            rect[2] = 0x180;
        }
        func_26EBC0(layer, i != 0 ? D_004260F0 : D_00426100, fr->handle);
        func_26EC48(layer, fr->handle, rect);
    }
}

void func_003D4518(u8 *obj) {
    struct Frame fr;
    u8 *layer = obj + 0xF8;
    u8 *g = D_3876A4;
    s32 mode = *(s32 *)(g + 0x8C);
    s32 row;
    s32 i;

    /* guide character: eye, mouth and text window depending on the screen mode */
    if (mode == 1) {
        func_26EBC0(layer, D_00425FA8, fr.handle);
        func_2495A8(layer, fr.handle, obj + 0x3334, 1);
        func_26EBC0(layer, D_00425F88, fr.handle);
        func_249778(layer, fr.handle, obj + 0x3338, 3);
        if (!(O_S32(0x2BC) & 8)) {
            func_26EBC0(layer, D_00425F98, fr.handle);
            func_249FB8(layer, fr.handle, 0, 0, O_S32(0x20), O_S32(0x2C0), 0);
        }
    } else if (mode < 2) {
        if (mode == 0) {
            func_26EBC0(layer, D_00425F88, fr.handle);
            func_249948(layer, fr.handle, obj + 0x3338, 1);
            if (!(O_S32(0x2BC) & 8)) {
                func_26EBC0(layer, D_00425F98, fr.handle);
                func_249FB8(layer, fr.handle, 0, 0, O_S32(0x20), O_S32(0x2C0), 1);
            }
        }
    } else if (mode == 2) {
        s32 speech;

        func_26EBC0(layer, D_00425FA8, fr.handle);
        func_2495A8(layer, fr.handle, obj + 0x3334, 1);
        func_26EBC0(layer, D_00425F88, fr.handle);
        if (O_S32(0x2CC) == 0) {
            func_249778(layer, fr.handle, obj + 0x3338, 3);
        } else {
            func_2498D8(layer, fr.handle, 3);
        }
        if (!(O_S32(0x2BC) & 8)) {
            speech = O_S32(0x2CC) != 0 ? O_S32(0x2C) : O_S32(0x20);
            func_26EBC0(layer, D_00425F98, fr.handle);
            func_249FB8(layer, fr.handle, 0, 0, speech, O_S32(0x2C0), 0);
        }
    }

    /* round counter ("kaisu") and its question mark ("kaiq") */
    row = PickKaisenRow(obj);
    fr.rect[0] = 0;
    fr.rect[1] = row << 5;
    fr.rect[2] = 0x100;
    fr.rect[3] = (row << 5) + 0x20;
    func_26EBC0(layer, D_00425FB8, fr.handle);
    func_26EC48(layer, fr.handle, fr.rect);

    row = *(s32 *)(D_3876A4 + 0x90);
    fr.rect[2] = 0x100;
    fr.rect[0] = 0;
    fr.rect[1] = row << 5;
    fr.rect[3] = (row << 5) + 0x20;
    func_26EBC0(layer, D_00425FC8, fr.handle);
    func_26EC48(layer, fr.handle, fr.rect);

    /* button icon */
    func_26EBC0(layer, D_00425FD0, fr.handle);
    if (*(u32 *)(D_3876A4 + 0x18) & 0x10) {
        if (!(O_S32(0x2BC) & 4)) {
            func_26EFC8(layer, fr.handle, 8);
        } else {
            func_26EFC8(layer, fr.handle, 4);
        }
    } else if ((O_S32(0x2BC) & 4) || O_S32(0x2C0) != -1) {
        func_26EFC8(layer, fr.handle, 4);
    } else {
        func_26EFC8(layer, fr.handle, 8);
    }

    /* tournament frames and fighter portraits (layer +0x30) */
    layer = obj + 0x30;
    if (O_S32(0x331C) > 0) {
        u8 *ent = obj + 0x3330;
        char *nameBuf = fr.nameBuf;

        for (i = 0; i < O_S32(0x331C); i++, ent += 0x20) {
            u32 flags;

            func_325830(nameBuf, D_00425FE0, i);
            func_26EBC0(layer, nameBuf, fr.handle);
            flags = *(u16 *)(ent + 0xC);
            if (flags & 1) {
                u32 tile = *(u16 *)(ent + 0x12);
                s32 x = (tile & 3) << 6;
                s32 y = (tile >> 2) << 6;

                fr.tileRectA[0] = x;
                fr.tileRectA[1] = y;
                fr.tileRectA[2] = x + 0x40;
                fr.tileRectA[3] = y + 0x40;
                func_26EC18(layer, fr.handle, 1);
                func_26EC48(layer, fr.handle, fr.tileRectA);
                flags = *(u16 *)(ent + 0xC);
            }
            if (flags & 2) {
                func_26EF88(layer, fr.handle, 0x1.333332p-1f);
            }
            func_325830(nameBuf, D_00425FF8, i);
            func_26EBC0(layer, nameBuf, fr.handle);
            {
                s32 *pos = (s32 *)(O_S32(0x3304) + *(u16 *)(ent + 0x14) * 12);

                func_26EEC8(layer, fr.handle, pos[1], pos[2]);
            }
            if (*(u16 *)(ent + 0xC) & 8) {
                func_26EFC8(layer, fr.handle, 8);
            } else {
                func_26EFC8(layer, fr.handle, 4);
            }
            if (*(u16 *)(ent + 0xC) & 2) {
                func_26EF88(layer, fr.handle, 0x1.333332p-1f);
            }
        }
    }

    /* scroll arrows */
    if (*(s32 *)(D_3876A4 + 0x90) != 0) {
        __builtin_memcpy(fr.scrollRect, D_00426010, 20);
        func_26EBC0(layer, D_00426028, fr.handle);
        func_26EC48(layer, fr.handle, fr.scrollRect);
        if (O_S32(0x2BC) & 4) {
            if ((s32)O_F32(0x3330) == O_S32(0x3328)) {
                func_26EFC8(layer, fr.handle, 0x48);
            } else {
                func_26EFC8(layer, fr.handle, 0x44);
            }
        } else {
            func_26EFC8(layer, fr.handle, 0x48);
        }
        func_26EBC0(layer, D_00426040, fr.handle);
        func_26EFC8(layer, fr.handle, 0x40);
        if (O_S32(0x2BC) & 4) {
            if ((s32)O_F32(0x3330) == 0) {
                func_26EFC8(layer, fr.handle, 0x48);
            } else {
                func_26EFC8(layer, fr.handle, 0x44);
            }
        } else {
            func_26EFC8(layer, fr.handle, 0x48);
        }
    }
    func_26EB20(layer, (s32)O_F32(0x3330), 0);

    /* layers +0x58 and +0x80: tile frames of the current selection */
    DrawTileFrames(obj, obj + 0x58, &fr, fr.tileRectB);
    DrawTileFrames(obj, obj + 0x80, &fr, fr.tileRectC);

    /* layer +0x120: names, round counter, vs numbers */
    layer = obj + 0x120;
    if (func_26EB70(layer) & 1) {
        DrawNamesAndRound(obj, layer, &fr, fr.rectD);
        DrawVsNumbers(obj, layer, &fr, fr.rectD);
    }

    /* layer +0x148: same plus victory / defeat marks */
    layer = obj + 0x148;
    if (func_26EB70(layer) & 1) {
        DrawNamesAndRound(obj, layer, &fr, fr.rectE);
        for (i = 0; i < 2; i++) {
            s32 mark;

            if (func_003D83D0(obj)) {
                mark = ((O_S32(0x2C8) ^ i) != 0) ? 2 : 3;
            } else {
                mark = (O_S32(0x2C8) ^ i) == 0;
            }
            fr.rectE[0] = 0;
            fr.rectE[1] = mark << 6;
            fr.rectE[2] = 0x100;
            fr.rectE[3] = (mark << 6) + 0x40;
            func_26EBC0(layer, i != 0 ? D_00426110 : D_00426128, fr.handle);
            func_26EC48(layer, fr.handle, fr.rectE);
        }
        DrawVsNumbers(obj, layer, &fr, fr.rectE);
    }
}
