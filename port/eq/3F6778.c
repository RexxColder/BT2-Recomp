#include "common.h"

/* Menu overlay: memory-card course/level select screen, draws the Flash layers each frame. */
extern u8 *D_0042A578;  /* menu object */
extern u8 *D_00387F2C;  /* save data buffer */

void func_00277E70(u8 *dst, s32 val, s64 n);
void func_0026EBC0(u8 *layer, const char *name, u8 *ref);
void func_0026EC48(u8 *layer, u8 *ref, s32 *rect);
void func_0026EC18(u8 *layer, u8 *ref, s32 frame);
void func_0026EFC8(u8 *layer, u8 *ref, s32 prop);
void func_0026ED60(u8 *layer, u8 *ref, s32 *rect, f32 *a3, f32 *a4, f32 f12, f32 f13);
void func_0026EB20(u8 *layer, s32 a1, s32 a2);
s32 func_0026EA58(u8 *layer);
void func_0024A598(u8 *layer, u8 *ref, s32 a2, s32 a3, u8 *a4, s32 a5, s32 a6);
void func_0024A6D8(u8 *layer, u8 *ref, s32 a2, s32 a3, u8 *a4, s32 a5, s32 a6, s32 a7, s32 a8);
void Num_ToDigits(u8 *digits, s32 value, s32 count, s32 zeroPad);
void Num_DrawDigits(u8 *layer, u8 *refs, s32 x, s32 y, u8 *cells, u8 *digits);
void func_0024A8A0(u8 *digits, s32 value, s32 count);
s32 func_00325830(u8 *buf, const char *fmt, ...);

#define W32(off)   (*(s32 *)(D_0042A578 + (off)))
#define SEL        (*(s32 *)(D_0042A578 + 0x14C + 4 * W32(0x140)))   /* selected course */
#define ENTRY      (*(u8 **)(D_0042A578 + 0x1C4) + 56 * SEL)         /* course table entry */
#define ENTRY_W(o) (*(s32 *)(ENTRY + (o)))

/* tower frame for a non-edge position v of a list of `limit` entries */
static s32 TowerParityFrame(s32 v, s32 limit) {
    if (limit & 1) {
        if (v == 0) {
            return 6;
        }
        return (v & 1) ? 0 : 1;
    }
    if (v == 0) {
        return 5;
    }
    return (v & 1) ? 1 : 0;
}

s32 func_003F6778(void) {
    u8 *ui;
    u8 *tw;
    u8 ref[16];
    s32 rc[8];  /* x0, y0, x1, y1 */
    u8 nameBuf[32];
    u8 courseRefs[16];
    u8 courseDigits[16];
    u8 scoreBuf[32];
    u8 scoreRefs[64];
    u8 scoreDigits[16];
    s32 i;
    s32 v;
    s32 limit;
    s32 frame;
    s32 sel;
    s32 mark;
    s32 r;
    const char *nm;

    func_00277E70(*(u8 **)(D_0042A578 + 0xB0), 0, 128);
    ui = D_0042A578 + 0x88;

    func_0026EBC0(ui, "mc_dummy_text_1", ref);
    func_0024A598(ui, ref, 4, 4, *(u8 **)(D_0042A578 + 0xC), SEL + 0x2F, 0);
    func_0026EBC0(ui, "mc_dummy_text_2", ref);
    func_0024A6D8(ui, ref, 4, 4, *(u8 **)(D_0042A578 + 0xC), SEL + 0x3E, 0, 0xFF303080, 0x20202040);

    rc[1] = 32;
    rc[3] = 64;
    rc[2] = 512;
    rc[0] = 0;
    func_0026EBC0(ui, "mc_menu_level", ref);
    func_0026EC48(ui, ref, rc);

    sel = SEL;
    rc[1] = ((sel % 8) % 4) << 6;
    rc[3] = rc[1] + 64;
    sel = SEL;
    rc[0] = ((sel % 8) / 4) << 8;
    rc[2] = rc[0] + 256;
    func_0026EBC0(ui, "mc_couse_name", ref);
    func_0026EC48(ui, ref, rc);
    func_0026EC18(ui, ref, SEL / 8);

    limit = ENTRY_W(8);
    rc[2] = 256;
    rc[0] = 0;
    rc[3] = 32 * limit;
    rc[1] = 32 * limit - 32;
    func_0026EBC0(ui, "mc_all_battle_text", ref);
    func_0026EC48(ui, ref, rc);

    for (i = 0; i < 2; i++) {
        func_00325830(nameBuf, "mc_couse_number%d", 1 - i);
        func_0026EBC0(ui, (const char *)nameBuf, courseRefs + 8 * i);
    }
    Num_ToDigits(courseDigits, SEL + 1, 2, 1);
    Num_DrawDigits(ui, courseRefs, 0, 0, *(u8 **)(D_0042A578 + 0x1CC), courseDigits);

    for (i = 0; i < 7; i++) {
        func_00325830(scoreBuf, "mc_score_number%d", 7 - i);
        func_0026EBC0(ui, (const char *)scoreBuf, scoreRefs + 8 * i);
    }
    sel = SEL;
    if (*(s8 *)(D_00387F2C + sel + 0x2C0) != 0) {
        func_0024A8A0(scoreDigits,
                      100 * *(u16 *)(D_00387F2C + 0x20E + 4 * (15 * W32(0x144) + sel)), 7);
    } else {
        __builtin_memset(scoreDigits, 11, 7);
        scoreDigits[7] = 0xFF;
    }
    Num_DrawDigits(ui, scoreRefs, 0, 0, *(u8 **)(D_0042A578 + 0x1D0), scoreDigits);

    if (*(s8 *)(D_00387F2C + SEL + 0x2C0) != 0) {
        func_0026EBC0(ui, "mc_clearmark", ref);
        func_0026EFC8(ui, ref, 4);
        mark = *(s8 *)(D_00387F2C + SEL + 0x2C0) - 1;
        rc[1] = 32 * (mark / 2);
        rc[3] = rc[1] + 32;
        mark = *(s8 *)(D_00387F2C + SEL + 0x2C0) - 1;
        rc[0] = 32 * (mark % 2);
        rc[2] = rc[0] + 32;
        func_0026EC48(ui, ref, rc);
        func_0026EBC0(ui, "mc_new_icon", ref);
        func_0026EFC8(ui, ref, 8);
    } else {
        func_0026EBC0(ui, "mc_clearmark", ref);
        func_0026EFC8(ui, ref, 8);
        func_0026EBC0(ui, "mc_new_icon", ref);
        if ((*(s32 *)(D_00387F2C + 0x208) & (2 << SEL)) != 0) {
            func_0026EFC8(ui, ref, 8);
        } else {
            func_0026EFC8(ui, ref, 4);
        }
    }

    for (i = 0; i < 3; i++) {
        func_00325830(nameBuf, "mc_level_box_%d", i + 1);
        func_0026EBC0(ui, (const char *)nameBuf, ref);
        rc[0] = i << 6;
        rc[1] = 0;
        rc[2] = (i << 6) + 64;
        rc[3] = 64;
        func_0026EC48(ui, ref, rc);
        func_0026EC18(ui, ref, (i ^ W32(0x144)) == 0);
    }

    rc[0] = 16;
    rc[1] = 0;
    rc[2] = 32;
    rc[3] = 32;
    func_0026EBC0(ui, "mc_yazirushi_course_r", ref);
    func_0026EC48(ui, ref, rc);
    func_0026EBC0(ui, "mc_yazirushi_level_r", ref);
    func_0026EC48(ui, ref, rc);
    if (W32(0x198) == 0) {
        func_0026EBC0(ui, "mc_yazirushi_course", ref);
        func_0026EFC8(ui, ref, 4);
        func_0026EBC0(ui, "mc_yazirushi_level", ref);
        func_0026EFC8(ui, ref, 8);
    } else if (W32(0x198) == 1) {
        func_0026EBC0(ui, "mc_yazirushi_course", ref);
        func_0026EFC8(ui, ref, 8);
        func_0026EBC0(ui, "mc_yazirushi_level", ref);
        func_0026EFC8(ui, ref, 4);
    } else {
        func_0026EBC0(ui, "mc_yazirushi_course", ref);
        func_0026EFC8(ui, ref, 8);
        func_0026EBC0(ui, "mc_yazirushi_level", ref);
        func_0026EFC8(ui, ref, 8);
    }

    /* clouds: layer 1 (+0x10) and layer 2 (+0x60) */
    rc[3] = 256;
    rc[2] = 512;
    rc[1] = 0;
    rc[0] = 0;
    for (i = 0; i < 2; i++) {
        u8 *layer = D_0042A578 + (i ? 0x60 : 0x10);
        func_0026EBC0(layer, i ? "mc_cloud_1" : "mc_cloud_2", ref);
        func_0026EC18(layer, ref, i ^ 1);
        func_0026ED60(layer, ref, rc, (f32 *)(D_0042A578 + 0x1BC + 4 * i), 0,
                      i ? -0.5f : -0x1.999998p-3f, 0.0f);
    }

    /* towers */
    tw = D_0042A578 + 0x38;
    func_0026EB20(tw, (s32) * (f32 *)(D_0042A578 + 0x1B8), 0);
    for (i = 0; i < 3; i++) {
        func_00325830(nameBuf, "mc_tower_%d", i + 1);
        func_0026EBC0(tw, (const char *)nameBuf, ref);
        v = W32(0x1A0) + i;
        limit = ENTRY_W(8);
        if (v < limit) {
            if (v == -1) {
                frame = 2;
            } else {
                frame = TowerParityFrame(v, limit);
            }
        } else if (v == limit + 1) {
            frame = 3;
        } else {
            frame = 4;
        }
        func_0026EC18(tw, ref, frame);
    }
    for (i = 0; i < 2; i++) {
        v = W32(0x1A4 + 4 * i);
        limit = ENTRY_W(8);
        if (v == limit + 1) {
            frame = 3;
        } else if (v == limit) {
            frame = 4;
        } else if (v == -1) {
            frame = 2;
        } else {
            frame = TowerParityFrame(v, limit);
        }
        func_0026EBC0(tw, i ? "mc_tower_5" : "mc_tower_4", ref);
        func_0026EC18(tw, ref, frame);
    }

    /* character plates */
    for (i = 0; i < 3; i++) {
        func_00325830(nameBuf, "mc_charaplate_%d", i + 1);
        func_0026EBC0(tw, (const char *)nameBuf, ref);
        if (W32(0x1A0) + i >= ENTRY_W(8)) {
            func_0026EFC8(tw, ref, 8);
        } else {
            func_0026EFC8(tw, ref, 4);
            if (W32(0x1A0) == ~i) {
                func_0026EC18(tw, ref, 8);
            } else {
                r = ENTRY_W(12);
                if (r == 2 || r == 4) {
                    func_0026EC18(tw, ref, 6);
                } else {
                    func_0026EC18(tw, ref, 7);
                }
            }
        }
    }
    func_0026EBC0(tw, "mc_charaplate_4", ref);
    if (W32(0x1A4) >= ENTRY_W(8)) {
        func_0026EFC8(tw, ref, 8);
    } else {
        func_0026EFC8(tw, ref, 4);
        if (W32(0x1A4) == -1) {
            func_0026EC18(tw, ref, 8);
        } else {
            r = ENTRY_W(12);
            if (r == 2 || r == 4) {
                func_0026EC18(tw, ref, 6);
            } else {
                func_0026EC18(tw, ref, 7);
            }
        }
    }

    /* rank numbers */
    for (i = 0; i < 3; i++) {
        func_00325830(nameBuf, "mc_rank_number%d2", i + 1);
        func_0026EBC0(tw, (const char *)nameBuf, ref);
        v = W32(0x1A0) + i;
        if (v >= ENTRY_W(8)) {
            func_0026EFC8(tw, ref, 8);
        } else if (v == -1) {
            func_0026EFC8(tw, ref, 8);
        } else {
            rc[1] = 32 * ((v + 1) / 5);
            rc[3] = rc[1] + 32;
            rc[0] = 16 * ((W32(0x1A0) + i + 1) % 5);
            rc[2] = rc[0] + 16;
            func_0026EC48(tw, ref, rc);
            func_0026EFC8(tw, ref, 4);
        }
    }
    func_0026EBC0(tw, "mc_rank_number42", ref);
    v = W32(0x1A4);
    if (v >= ENTRY_W(8)) {
        func_0026EFC8(tw, ref, 8);
    } else if (v == -1) {
        func_0026EFC8(tw, ref, 8);
    } else {
        rc[1] = 32 * ((v + 1) / 5);
        rc[3] = rc[1] + 32;
        rc[0] = 16 * ((W32(0x1A4) + 1) % 5);
        rc[2] = rc[0] + 16;
        func_0026EC48(tw, ref, rc);
        func_0026EFC8(tw, ref, 4);
    }

    for (i = 0; i < 4; i++) { /* asm 0x3F76B8: li s3,3 + bgezl -> 4 passes (class 9) */
        r = func_0026EA58(D_0042A578 + 0x10 + 40 * i);
    }
    return r;
}
