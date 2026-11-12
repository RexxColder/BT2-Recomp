#include "common.h"

/* menu overlay: character-select screen UI update (two players) */

void func_00277E70(u8 *dst, s32 val, s64 n);
void func_0026EB20(u8 *h, s32 a, s32 b);
s32 func_0026EB70(u8 *h);
void func_0026EA58(u8 *h);
void func_0026EBC0(u8 *h, const char *name, u8 *obj);
void func_0026EEF8(u8 *h, u8 *obj, f32 f);
void func_0026EEC8(u8 *h, u8 *obj, s32 x, s32 y);
void func_0026EC48(u8 *h, u8 *obj, s32 *rect);
void func_0026EC18(u8 *h, u8 *obj, s32 n);
void func_0026EFC8(u8 *h, u8 *obj, s32 anim);
f32 func_0026F148(u8 *h, u8 *obj);
s32 func_0024B6C8(s32 v);
void func_00249BB8(u8 *h, u8 *obj, s32 a, s32 b, s32 c, s32 d, s32 e);
void func_00249DB8(u8 *h, u8 *obj, s32 a, s32 b, s32 c, s32 d, s32 e);
s32 func_00325830(u8 *buf, const char *fmt, s32 n);

extern u8 *D_0042A570 __attribute__((section(".data")));   /* menu state */
extern u8 *D_003876A4;   /* game settings */
extern u8 D_0042A660[765] __attribute__((section(".data")));
extern u8 D_0042A9A0[120] __attribute__((section(".data")));
extern u8 D_0042AAA0[20] __attribute__((section(".data")));

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F(p, o) (*(f32 *)((u8 *)(p) + (o)))

struct Frame {
    u8 obj[16];
    s32 rect[4];
    u8 pad0[16];
    u8 text[768];
    u8 obj2[16];
    s32 palette[32];
    s32 mode[2];
    u8 pad1[8];
    u8 name[128];
    u8 obj3[16];
    s32 rect2[4];
    u8 pad2[16];
    s32 rect3[5];
};

void func_003F16E0(void) {
    struct Frame f;
    u8 *m;
    u8 *h;
    u8 *gs;
    s32 i, j, k, n, c, idx, nameId, off, xofs, yofs;
    s32 *cur;

    func_00277E70(*(u8 **)(D_0042A570 + 0x114), 0, 0x80);
    h = D_0042A570 + 0x4C;

    /* gauge fade for both players */
    off = 0x36B0;
    for (i = 0; i < 2; i++) {
        m = D_0042A570;
        if (W(m, 0x218) & (0x40 << i)) {
            F(m, 0xC + off) = F(m, 0xC + off) + 0.075f;
            if (!(1.0f <= F(D_0042A570, 0xC + off))) {
                goto name_done;
            }
            F(D_0042A570, 0xC + off) = 1.0f;
        } else {
            W(m, 0xC + off) = 0;
        }
    name_done:
        func_0026EBC0(h, i == 0 ? "mc_single_chara_l" : "mc_single_chara_r", f.obj);
        func_0026EEF8(h, f.obj, F(D_0042A570, 0xC + off));
        off += 4;
    }

    /* name and form text */
    for (i = 0; i < 2; i++) {
        m = D_0042A570;
        idx = 7 * W(m, 0x224 + 4 * i) + W(m, 0x21C + 4 * i);
        nameId = 0x84;
        if (idx < 0x4A) {
            nameId = W(*(u8 **)(m + 0x258 + 4 * i), 44 * idx);
        }
        func_0026EBC0(h, i != 0 ? "mc_name_text_l" : "mc_name_text_r", f.obj);
        func_00249BB8(h, f.obj, 0, 0, W(D_0042A570, 0x1C), nameId, i == 0 ? 2 : 0);
        func_0026EBC0(h, i != 0 ? "mc_form_text_l" : "mc_form_text_r", f.obj);
        func_00249DB8(h, f.obj, 0, 0, W(D_0042A570, 0x20), nameId, i == 0 ? 2 : 0);
    }
    func_0026EBC0(h, "mc_name_plate_turn", f.obj);
    func_0026EFC8(h, f.obj, 0x10);

    /* course name */
    gs = D_003876A4;
    n = W(gs, 0x64) % 8;
    f.rect[1] = (n % 4) << 6;
    f.rect[3] = f.rect[1] + 0x40;
    n = W(gs, 0x64) % 8;
    f.rect[0] = (n / 4) << 8;
    f.rect[2] = f.rect[0] + 0x100;
    func_0026EBC0(h, "mc_couse_name", f.obj);
    func_0026EC48(h, f.obj, f.rect);
    func_0026EC18(h, f.obj, W(D_003876A4, 0x64) / 8);

    /* level box */
    f.rect[3] = 0x40;
    f.rect[1] = 0;
    f.rect[0] = W(D_003876A4, 0x58) << 6;
    f.rect[2] = f.rect[0] + 0x40;
    func_0026EBC0(h, "mc_level_box_1", f.obj);
    func_0026EC48(h, f.obj, f.rect);
    func_0026EC18(h, f.obj, 1);

    /* type text (three 255-byte strings, local copy) */
    __builtin_memcpy(f.text, D_0042A660, 765);
    off = 0;
    for (i = 0; i < 2; i++) {
        u8 *p;

        h = D_0042A570 + off + 0xC4;
        func_0026EB20(h, 0, 0xA6);
        func_0026EBC0(h, "mc_type_text_onanime", f.obj2);
        k = W(D_0042A570, 0x234 + 4 * i);
        func_0026EEC8(h, f.obj2, 0, 22 * k);
        func_0026EBC0(h, (const char *)(f.text + 255 * W(D_0042A570, 0x234 + 4 * i)), f.obj);
        {
            f32 r = func_0026F148(h, f.obj);
            func_0026EEF8(h, f.obj2, r);
        }
        k = W(D_0042A570, 0x234 + 4 * i);
        f.rect[2] = 0x100;
        f.rect[0] = 0;
        f.rect[1] = 32 * k;
        f.rect[3] = 32 * k + 32;
        func_0026EBC0(h, "type_text_on", f.obj);
        func_0026EC48(h, f.obj, f.rect);
        if (i == 0) {
            func_0026EBC0(h, "mc_type_plate_turn", f.obj);
            func_0026EFC8(h, f.obj, 0x10);
        }
        p = f.text;
        for (j = 0; j < 3; j++) {
            f.rect[1] = 32 * j;
            f.rect[3] = 32 * j + 32;
            f.rect[0] = 0;
            f.rect[2] = 0x100;
            func_0026EBC0(h, (const char *)p, f.obj);
            p += 255;
            func_0026EC48(h, f.obj, f.rect);
        }
        off += 0x28;
    }

    /* colour selector */
    __builtin_memcpy(f.palette, D_0042A9A0, 120);
    off = 0;
    for (i = 0; i < 2; i++) {
        s32 selOff = 0x240 + 4 * i;
        s32 curOff = 0x230 + 4 * i;

        n = func_0024B6C8(W(D_0042A570, selOff + 0xC));
        xofs = (n < 3) ? 25 : 0;
        f.mode[0] = xofs;
        n = func_0024B6C8(W(D_0042A570, selOff + 0xC));
        yofs = (n < 4) ? 14 : 0;
        f.mode[1] = yofs;
        h = D_0042A570 + off + 0xC4;
        func_0026EBC0(h, "mc_select_color_on", f.obj3);
        c = W(D_0042A570, curOff + 0xC);
        func_0026EEC8(h, f.obj3, f.mode[0] + 50 * (c % 3), f.mode[1] + 28 * (c / 3));
        func_0026EC48(h, f.obj3, &f.palette[5 * W(D_0042A570, curOff + 0xC)]);
        for (j = 0; j < 6; j++) {
            func_00325830(f.name, "mc_select_color_off_%d", j + 1);
            func_0026EBC0(h, (const char *)f.name, f.obj3);
            func_0026EC48(h, f.obj3, &f.palette[5 * j]);
            func_0026EEC8(h, f.obj3, f.mode[0], f.mode[1]);
            if (j < func_0024B6C8(W(D_0042A570, selOff + 0xC))) {
                func_0026EFC8(h, f.obj3, 4);
            } else {
                func_0026EFC8(h, f.obj3, 8);
            }
            if (j == W(D_0042A570, curOff + 0xC)) {
                f32 r = func_0026F148(h, f.obj3);
                func_0026EBC0(h, "mc_select_color_on", f.obj3);
                func_0026EEF8(h, f.obj3, r);
            }
        }
        off += 0x28;
    }

    /* character cursors */
    off = 0;
    for (i = 0; i < 2; i++, off += 0x28) {
        s32 colOff = 0x210 + 4 * i;

        f.mode[0] = 0;
        f.mode[1] = 0;
        if (!(func_0026EB70(D_0042A570 + off + 0x74) & 1)) {
            continue;
        }
        h = D_0042A570 + off + 0x74;
        func_0026EB20(h, 0, i == 0 ? 0x18 : 0x168);
        cur = &f.mode[i];
        m = D_0042A570;
        if (W(m, 0x218) & (0x1000 << i)) {
            *cur = 1;
        }
        if (W(m, 0x218) & (0x100 << i)) {
            *cur = 2;
        }
        if (!(W(m, 0x218) & 0x100)) {
            f.mode[1] = 2;
        }
        func_0026EBC0(h, "mc_chara_cursor", f.obj);
        func_0026EEC8(h, f.obj, 60 * W(D_0042A570, colOff + 0xC), 0);
        if (*cur == 1) {
            func_0026EFC8(h, f.obj, 2);
        } else if (*cur == 2) {
            func_0026EFC8(h, f.obj, 8);
        } else {
            func_0026EFC8(h, f.obj, 5);
        }
        f.rect2[0] = 0x20;
        f.rect2[1] = 0;
        f.rect2[2] = 0x40;
        f.rect2[3] = 0x20;
        func_0026EBC0(h, "mc_r_button", f.obj);
        func_0026EC48(h, f.obj, f.rect2);
        func_0026EBC0(h, "mc_lr_buttonanime", f.obj);
        func_0026EEC8(h, f.obj, 60 * W(D_0042A570, colOff + 0xC), 0);
        if (*cur == 1) {
            func_0026EFC8(h, f.obj, 2);
        } else if (*cur == 2) {
            func_0026EFC8(h, f.obj, 8);
        } else {
            m = D_0042A570;
            idx = 7 * W(m, 0x224 + 4 * i) + W(m, colOff + 0xC);
            if (W(*(u8 **)(m + 0x258 + 4 * i), 44 * idx + 4) != 0) {
                func_0026EFC8(h, f.obj, 4);
            } else {
                func_0026EFC8(h, f.obj, 8);
            }
            func_0026EFC8(h, f.obj, 1);
        }
        func_0026EBC0(h, "mc_chara_select_yazirushi_anime", f.obj);
        if (*cur == 1) {
            func_0026EFC8(h, f.obj, 2);
        } else if (*cur == 2) {
            func_0026EFC8(h, f.obj, 8);
        } else {
            func_0026EFC8(h, f.obj, 5);
        }
        __builtin_memcpy(f.rect3, D_0042AAA0, 20);
        func_0026EBC0(h, "mc_chara_select_yazurushi_down", f.obj);
        func_0026EC48(h, f.obj, f.rect3);
    }

    off = 0;
    for (i = 4; i >= -1; i--) {
        func_0026EA58(D_0042A570 + off + 0x24);
        off += 0x28;
    }
}
