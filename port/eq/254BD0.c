#include "common.h"

extern void func_00277E70(u8 *dst, s32 val, s64 n);
extern void func_0026EBC0(u8 *layer, const char *name, u8 *out);
extern void func_0026EEF8(u8 *layer, u8 *ref, f32 f12);
extern s32 func_0026EFC8(u8 *layer, u8 *ref, s32 arg2);
extern s32 func_00249BB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
extern s32 func_00249DB8(u8 *layer, u8 *obj, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
extern s32 func_00325830(u8 *buf, const char *fmt, ...);
extern void func_0026EC48(u8 *layer, u8 *ref, u8 *rect);
extern void func_0026EC18(u8 *layer, u8 *ref, s32 arg2);
extern void func_0026EEC8(u8 *layer, u8 *ref, s32 x, s32 y);
extern void func_0026EB20(u8 *layer, s32 x, s32 y);
extern s32 func_0026EA58(u8 *layer);
extern void Num_ToDigits(u8 *digits, s32 value, s32 count, s32 zeroPad);
extern void Num_DrawDigits(u8 *layer, u8 *rects, s32 a2, s32 a3, u8 *font, u8 *digits);
extern void *func_002AD630(void);
extern void func_0024A6D8(u8 *layer, u8 *ref, s32 a2, s32 a3, s32 font, s32 id, s32 t2, s32 t3, s32 st0);
extern void func_0024A598(u8 *layer, u8 *ref, s32 a2, s32 a3, s32 font, s32 id, s32 t2);
extern u8 *D_003879D0;
extern f32 D_00386D80;

/* Draws the character-select screen layers (mc_* UI objects) for both sides. */
s32 func_00254BD0(void) {
    u8 sp[0x100];
    u8 *ui;
    u8 *layer;
    s32 side, i, j, row, k;
    s32 flags;
    s32 ret = 0;

    func_00277E70(*(u8 **)(D_003879D0 + 0x78), 0, 0x80);
    ui = D_003879D0;
    layer = ui + 0x28;
    for (side = 0; side < 2; side++) {
        flags = *(s32 *)(ui + 0x15C);
        if (!(flags & (0x10 << side)) || (flags & (0x200 << side))) {
            *(s32 *)(ui + side * 4 + 0x29C) = 0;
        } else {
            f32 *t = (f32 *)(ui + 0x29C + side * 4);

            *t = *t + D_00386D80;
            if (*(f32 *)(D_003879D0 + 0x29C + side * 4) >= 1.0f) {
                *(f32 *)(D_003879D0 + 0x29C + side * 4) = 1.0f;
            }
        }
        func_0026EBC0(layer, side != 0 ? "mc_single_chara_r" : "mc_single_chara_l", sp + 0x10);
        func_0026EEF8(layer, sp + 0x10, *(f32 *)(D_003879D0 + side * 4 + 0x29C));
        ui = D_003879D0;
    }
    func_0026EBC0(layer, "mc_name_plate_turn", sp + 0x10);
    func_0026EFC8(layer, sp + 0x10, 0x10);

    for (side = 0; side < 2; side++) {
        s32 name;

        ui = D_003879D0;
        if (side != 0) {
            name = *(s32 *)(ui + *(s32 *)(ui + 0x274) * 20 + 0x204);
        } else if (*(s32 *)(ui + 0x16C) == 1) {
            name = *(s32 *)(ui + *(s32 *)(ui + 0x160) * 8 + 0x174);
        } else {
            name = *(s32 *)(ui + *(s32 *)(ui + 0x168) * 20 + 0x1A0);
        }
        if (name < 0) {
            continue;
        }
        func_0026EBC0(layer, side != 0 ? "mc_name_text_l" : "mc_name_text_r", sp + 0x10);
        func_00249BB8(layer, sp + 0x10, 0, 2, *(s32 *)(D_003879D0 + 0x1C), name, side == 0 ? 2 : 0);
        func_0026EBC0(layer, side != 0 ? "mc_form_text_l" : "mc_form_text_r", sp + 0x10);
        func_00249DB8(layer, sp + 0x10, 0, -2, *(s32 *)(D_003879D0 + 0x20), name, side == 0 ? 2 : 0);
    }

    for (i = 0; i < 5; i++) {
        s32 off = 0x260;

        for (j = 0; j < 2; j++) {
            s32 q = i >> 2;

            func_00325830(sp + 0x40, j != 0 ? "mc_chara_plate_%d_e" : "mc_chara_plate_%d_p", i);
            func_0026EBC0(layer, (const char *)(sp + 0x40), sp + 0x10);
            if (i < *(s32 *)(D_003879D0 + off + 8)) {
                *(s32 *)(sp + 0x20) = (i - q * 4) << 7;
                *(s32 *)(sp + 0x24) = q << 7;
                *(s32 *)(sp + 0x28) = ((i - q * 4) << 7) + 0x80;
                *(s32 *)(sp + 0x2C) = (q << 7) + 0x80;
                func_0026EC48(layer, sp + 0x10, sp + 0x20);
                func_0026EFC8(layer, sp + 0x10, 4);
            } else {
                func_0026EFC8(layer, sp + 0x10, 8);
            }
            off += 4;
        }
    }

    for (i = 0; i < 5; i++) {
        func_00325830(sp + 0x60, "mc_csr_%d", i);
        func_0026EBC0(layer, (const char *)(sp + 0x60), sp + 0x10);
        if (i == *(s32 *)(D_003879D0 + 0x168)) {
            func_0026EFC8(layer, sp + 0x10, 4);
        } else {
            func_0026EFC8(layer, sp + 0x10, 8);
        }
    }

    for (side = 0; side < 2; side++) {
        for (j = 0; j < 4; j++) {
            func_00325830(sp + 0x80, side != 0 ? "mc_t_lv_e_%d" : "mc_t_lv_p_%d", 3 - j);
            func_0026EBC0(layer, (const char *)(sp + 0x80), sp + 0xA0 + j * 8);
        }
        Num_ToDigits(sp + 0xC0, *(s32 *)(D_003879D0 + 0x270 + side * 4 + 8), 4, 1);
        Num_DrawDigits(layer, sp + 0xA0, 0, 0, *(u8 **)(D_003879D0 + 0x290), sp + 0xC0);
    }

    for (row = 0; row < 5; row++) {
        for (j = 0; j < 3; j++) {
            func_00325830(sp + 0x80, "mc_lv_%d_%d_p", row, 2 - j);
            func_0026EBC0(layer, (const char *)(sp + 0x80), sp + 0xD0 + j * 8);
        }
        ui = D_003879D0;
        if (*(s32 *)(ui + 0x1A0 + row * 0x14) >= 0) {
            Num_ToDigits(sp + 0xF0, *(s32 *)(ui + 0x1A0 + row * 0x14 + 4), 3, 1);
            Num_DrawDigits(layer, sp + 0xD0, 0, 0, *(u8 **)(D_003879D0 + 0x290), sp + 0xF0);
        } else {
            sp[0xF0] = 10;
            sp[0xF1] = 10;
            sp[0xF2] = 10;
            sp[0xF3] = 0xFF;
            Num_DrawDigits(layer, sp + 0xD0, 0, 0, *(u8 **)(ui + 0x290), sp + 0xF0);
        }
    }

    for (row = 0; row < 5; row++) {
        for (j = 0; j < 3; j++) {
            func_00325830(sp + 0x80, "mc_lv_%d_%d_e", row, 2 - j);
            func_0026EBC0(layer, (const char *)(sp + 0x80), sp + 0xD0 + j * 8);
        }
        ui = D_003879D0;
        if (*(s32 *)(ui + 0x204 + row * 0x14) >= 0) {
            Num_ToDigits(sp + 0xF0, *(s32 *)(ui + 0x204 + row * 0x14 + 4), 3, 1);
            Num_DrawDigits(layer, sp + 0xD0, 0, 0, *(u8 **)(D_003879D0 + 0x290), sp + 0xF0);
        } else {
            sp[0xF0] = 10;
            sp[0xF1] = 10;
            sp[0xF2] = 10;
            sp[0xF3] = 0xFF;
            Num_DrawDigits(layer, sp + 0xD0, 0, 0, *(u8 **)(ui + 0x290), sp + 0xF0);
        }
    }

    for (i = 0; i < 2; i++) {
        *(s32 *)(sp + 0x24) = i << 5;
        *(s32 *)(sp + 0x2C) = (i << 5) + 0x20;
        *(s32 *)(sp + 0x20) = 0;
        *(s32 *)(sp + 0x28) = 0x100;
        func_00325830(sp + 0x80, "mc_confirmation_dummy_%d", i);
        func_0026EBC0(layer, (const char *)(sp + 0x80), sp + 0x10);
        func_0026EC48(layer, sp + 0x10, sp + 0x20);
    }
    k = *(s32 *)(D_003879D0 + 0x164);
    *(s32 *)(sp + 0x28) = 0x100;
    *(s32 *)(sp + 0x20) = 0;
    *(s32 *)(sp + 0x24) = k << 5;
    *(s32 *)(sp + 0x2C) = (k << 5) + 0x20;
    func_0026EBC0(layer, "mc_confirmation_on", sp + 0x10);
    func_0026EC48(layer, sp + 0x10, sp + 0x20);
    func_0026EC18(layer, sp + 0x10, 1);
    func_0026EBC0(layer, "mc_confirmation_csr", sp + 0x10);
    func_0026EEC8(layer, sp + 0x10, 0, *(s32 *)(D_003879D0 + 0x164) << 5);

    {
        s32 base = *(s32 *)((u8 *)func_002AD630() + 0xC);

        for (i = 0; i < 2; i++) {
            func_00325830(sp + 0xA0, "mc_dummy_rule_title%d", i + 1);
            func_0026EBC0(layer, (const char *)(sp + 0xA0), sp + 0x10);
            func_0024A6D8(layer, sp + 0x10, 0, 0, *(s32 *)(D_003879D0 + 0x24), i == 0 ? 0x192 : 0x183, 0,
                          (s32)0xFCF5DE80, (s32)0x874F1480);
            func_00325830(sp + 0xA0, "mc_dummy_rule_text%d", i + 1);
            func_0026EBC0(layer, (const char *)(sp + 0xA0), sp + 0x10);
            func_0024A598(layer, sp + 0x10, 0, 0, *(s32 *)(D_003879D0 + 0x24),
                          i == 0 ? base + 0x193 : base + 0x184, 0);
        }
    }

    layer = D_003879D0 + 0x50;
    func_0026EB20(layer, 0, 0x10);
    func_0026EBC0(layer, "mc_chara_cursor", sp + 0x10);
    func_0026EEC8(layer, sp + 0x10, *(s32 *)(D_003879D0 + 0x160) * 60, 0);
    k = 0;
    i = 1;
    do {
        i--;
        ret = func_0026EA58(D_003879D0 + k + 0x28);
        k += 0x28;
    } while (i >= 0);
    return ret;
}
