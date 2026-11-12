#include "common.h"

extern void func_00277E70(s32 arg0, s32 arg1, s64 arg2);
extern s32 func_00325830(char *buf, const char *fmt, ...);
extern void func_0026EBC0(u8 *ui, char *name, u8 *out);
extern void func_0024A598(u8 *ui, u8 *rect, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_0026EFC8(u8 *ui, u8 *rect, s32 arg2);
extern void func_0026EC48(u8 *ui, u8 *rect, s32 *box);
extern void func_0026EC18(u8 *ui, u8 *rect, s32 arg2);
extern void func_0024A8A0(u8 *digits, s32 value, s32 count);
extern void func_0024AB10(u8 *ui, u8 *rects, s32 arg2, s32 arg3, s32 font, u8 *digits);
extern void func_0024A9D0(u8 *digits, s32 value, s32 count, s32 arg3);
extern void func_00249BB8(u8 *ui, u8 *rect, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_00249DB8(u8 *ui, u8 *rect, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern s32 func_0026EA58(u8 *ui);
extern u8 *D_003879F8;

#define ST() (D_003879F8)
#define W(off) (*(s32 *)(ST() + (off)))

s32 func_00257930(void) {
    u8 rect[16];
    s32 box[4];
    char nbuf[32];
    char nbuf2[32];
    char nbuf3[32];
    u8 expRects[48];
    u8 expDigits[16];
    u8 zenRects[64];
    u8 zenDigits[16];
    char nbuf4[32];
    char nbuf5[32];
    u8 lvRects[32];
    u8 lvDigits[16];
    u8 *ui;
    s32 i, j;

    func_00277E70(W(0x40), 0, 0x80);
    ui = ST() + 0x18;
    if (W(0xA4) & 0x800) {
        for (i = 0; i < 3; i++) {
            func_00325830(nbuf, "mc_item_name_%d", i);
            func_0026EBC0(ui, nbuf, rect);
            if (i < W(0xB4)) {
                func_0024A598(ui, rect, 8, 0, W(0x14), W(0xCC + i * 4) + 1, 0);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        func_00325830(nbuf2, "mc_pay_icon_%d", i);
        func_0026EBC0(ui, nbuf2, rect);
        if (i == 0) {
            box[0] = 0x40;
            box[1] = 0x40;
            box[2] = 0x80;
            box[3] = 0x80;
            func_0026EC48(ui, rect, box);
        } else if (i < W(0xB4) + 1 && (W(0xA4) & 0x800)) {
            s32 v;
            func_0026EFC8(ui, rect, 4);
            v = *(s32 *)(*(u8 **)(ST() + 0x108) + W(0xC8 + i * 4) * 48 + 8);
            box[1] = (v / 4) << 6;
            box[3] = box[1] + 0x40;
            v = *(s32 *)(*(u8 **)(ST() + 0x108) + W(0xC8 + i * 4) * 48 + 8);
            box[0] = (v - (v / 4) * 4) << 6;
            box[2] = box[0] + 0x40;
            func_0026EC48(ui, rect, box);
        } else {
            func_0026EFC8(ui, rect, 8);
        }
    }
    for (i = 0; i < 5; i++) {
        func_00325830(nbuf3, "mc_exp_namber_%d", 4 - i);
        func_0026EBC0(ui, nbuf3, expRects + i * 8);
    }
    func_0024A8A0(expDigits, W(0xBC), 5);
    func_0024AB10(ui, expRects, 0, 0, W(0x114), expDigits);
    for (i = 0; i < 7; i++) {
        func_00325830(nbuf4, "mc_pay_zenny_point_%d", 6 - i);
        func_0026EBC0(ui, nbuf4, zenRects + i * 8);
    }
    func_0024A8A0(zenDigits, W(0xC4), 7);
    func_0024AB10(ui, zenRects, 0, 0, W(0x114), zenDigits);
    for (i = 0; i < 5; i++) {
        if (i < W(0xB8)) {
            s32 v = *(s32 *)(*(u8 **)(ST() + 0x118) + i * 16 + 8);
            func_00325830(nbuf5, "mc_name_%d", i);
            func_0026EBC0(ui, nbuf5, rect);
            func_00249BB8(ui, rect, 0, 0, W(0xC), v, 0);
            func_00325830(nbuf5, "mc_fome_%d", i);
            func_0026EBC0(ui, nbuf5, rect);
            func_00249DB8(ui, rect, 0, 0, W(0x10), v, 0);
        }
    }
    if (!(W(0xA4) & 0x7C)) {
        func_0026EBC0(ui, "mc_lv_up_text", rect);
        func_0026EFC8(ui, rect, 8);
    }
    for (i = 0; i < 5; i++) {
        if (!(W(0xA4) & (4 << i))) {
            func_00325830(nbuf, "mc_lv_up_icon_%d", i);
            func_0026EBC0(ui, nbuf, rect);
            func_0026EFC8(ui, rect, 8);
        }
    }
    for (i = 0; i < 5; i++) {
        func_00325830(nbuf, "mc_lv_icon_%d", i);
        func_0026EBC0(ui, nbuf, rect);
        if (W(0xA4) & (4 << i)) {
            func_0026EC18(ui, rect, 1);
        } else {
            func_0026EFC8(ui, rect, 8);
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            func_00325830(nbuf, "mc_lv_%d_%d_a", i, 2 - j);
            func_0026EBC0(ui, nbuf, lvRects + j * 8);
        }
        if (i < W(0xB8)) {
            func_0024A9D0(lvDigits, W(0xD8 + i * 8), 3, 1);
            func_0024AB10(ui, lvRects, 0, 0, W(0x114), lvDigits);
        } else {
            lvDigits[0] = 10;
            lvDigits[3] = 0xFF;
            lvDigits[1] = 10;
            lvDigits[2] = 10;
            func_0024AB10(ui, lvRects, 0, 0, W(0x114), lvDigits);
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            func_00325830(nbuf, "mc_lv_%d_%d_b", i, 2 - j);
            func_0026EBC0(ui, nbuf, lvRects + j * 8);
            func_0026EC18(ui, lvRects + j * 8, 1);
        }
        if (W(0xA4) & (4 << i)) {
            if (i < W(0xB8)) {
            func_0024A9D0(lvDigits, W(0xDC + i * 8), 3, 1);
                func_0024AB10(ui, lvRects, 0, 0, W(0x114), lvDigits);
            } else {
                lvDigits[0] = 10;
                lvDigits[3] = 0xFF;
                lvDigits[1] = 10;
                lvDigits[2] = 10;
                func_0024AB10(ui, lvRects, 0, 0, W(0x114), lvDigits);
            }
        } else {
            lvDigits[0] = 10;
            lvDigits[3] = 0xFF;
            lvDigits[1] = 10;
            lvDigits[2] = 10;
            func_0024AB10(ui, lvRects, 0, 0, W(0x114), lvDigits);
        }
    }
    return func_0026EA58(ST() + 0x18);
}
