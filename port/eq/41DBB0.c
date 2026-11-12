#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

void func_00277E70(u8 *a0, s32 a1, s32 a2);
void func_0041CC90(s32 a0);
extern s32 func_00325830();
extern s32 func_0026EBC0();
extern s32 func_002495A8();
extern s32 func_00249778();
extern s32 func_00249FB8();
extern s32 func_0024A598();
extern s32 func_0026EFC8();
extern s32 func_0026EC48();
extern s32 func_0026EC18();
extern s32 func_0026EEC8();
extern s32 func_0026F118();
extern s32 func_0024A6D8();
extern s32 func_0041C8D8();
extern s32 func_0024B468();
extern s32 func_0026EA58();
void func_0026EEF8(u8 *a0, u8 *a1, f32 f12);
void Num_ToDigits(u8 *digits, s32 value, s32 count, s32 zeroPad);
void Num_DrawDigits(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5);
void func_0024C060(void);

#define O D_0042FD74
#define W(off) (*(s32 *)(O + (off)))
#define CUR (*(s32 *)(O + 0x148 + W(0x1AC) * 4))
#define PC(off) (*(s32 *)(O + (off) + CUR * 4))

/* menu overlay draw of the "mc_*" achievement/guide screen */
void func_0041DBB0(void) {
    u8 sp10[16];
    s32 r[4];
    char nm[32];
    char nm2[32];
    u8 numb[32];
    u8 dig[16];
    char tbl[3][32] = {"mc_da_2_text_off_t", "mc_da_2_text_on", "mc_da_2_text_off_l"};
    char nm3[32];
    s32 px, py;
    s32 qx, qy;
    u8 *a0;
    s32 i, off, n, h, q, v, c;
    char *tp;
    s32 g;

    func_00277E70(*(u8 **)(O + 0x6C), 0, 0x80);
    func_0041CC90(W(0x324));
    a0 = O + 0x44;
    i = 0;
    do {
        if (i == W(0x324)) {
            func_00325830(nm, "mc_guide_eye_v%d", i);
            func_0026EBC0(a0, nm, sp10);
            func_002495A8(a0, sp10, O + 0x304 + i * 4, 1);
            func_00325830(nm, "mc_guide_mouth_v%d", i);
            func_0026EBC0(a0, nm, sp10);
            func_00249778(a0, sp10, O + 0x314 + i * 4, 3);
        }
        i++;
    } while (i < 4);

    func_0026EBC0(a0, "mc_textwindow", sp10);
    func_00249FB8(a0, sp10, 0, 0, *(u8 **)(O + 0x10), W(0x13C), 0);
    func_0026EBC0(a0, "mc_da_4_textwindow", sp10);
    func_0024A598(a0, sp10, 0x10, 0x24, *(u8 **)(O + 0x18), CUR + 0x16A, 0);
    func_0026EBC0(a0, "mc_button_icon2", sp10);
    if (W(0x134) & 0x20) {
        func_0026EFC8(a0, sp10, 8);
    } else {
        func_0026EFC8(a0, sp10, 4);
        r[1] = 0x20;
        r[3] = 0x40;
        r[2] = 0x100;
        r[0] = 0;
        func_0026EC48(a0, sp10, r);
    }

    if (W(0x134) & 8) {
        *(f32 *)(O + 0x144) = *(f32 *)(O + 0x144) + *(f32 *)&(u32){0x3D999999};
        if (1.0f <= *(f32 *)(O + 0x144)) {
            *(f32 *)(O + 0x144) = 1.0f;
        }
    } else {
        W(0x144) = 0;
    }

    func_0026EBC0(a0, "mc_guide_fullbody_right", sp10);
    func_0026EEF8(a0, sp10, *(f32 *)(O + 0x144));
    i = 0;
    do {
        func_00325830(nm2, "mc_achievementrate_number_%d", 2 - i);
        func_0026EBC0(a0, nm2, numb + i * 8);
        i++;
    } while (i < 3);
    Num_ToDigits(dig, W(0x2EC), 3, 1);
    Num_DrawDigits(a0, numb, 0, 0, *(u8 **)(O + 0x328), dig);

    r[3] = 0x40;
    r[2] = 0x20;
    r[1] = 0x20;
    r[0] = 0;
    func_0026EBC0(a0, "mc_da2_yazirusi_l", sp10);
    func_0026EC48(a0, sp10, r);
    if (W(0x134) & 0x10) {
        func_0026EBC0(a0, "mc_da2_yazirusi_t", sp10);
        func_0026EFC8(a0, sp10, PC(0x1B8) == 0 ? 8 : 4);
        func_0026EBC0(a0, "mc_da2_yazirusi_l", sp10);
        func_0026EFC8(a0, sp10, (PC(0x1B8) ^ (PC(0x21C) - 1)) == 0 ? 8 : 4);
    } else {
        func_0026EBC0(a0, "mc_da2_yazirusi_t", sp10);
        func_0026EFC8(a0, sp10, 4);
        func_0026EBC0(a0, "mc_da2_yazirusi_l", sp10);
        func_0026EFC8(a0, sp10, 4);
    }

    tp = &tbl[0][0];
    i = 0;
    do {
        func_0026EBC0(a0, tp, sp10);
        tp += 0x20;
        if (W(0x1B0) == 1 && (i == 0 || i == 2)) {
            func_0026EFC8(a0, sp10, 8);
            i++;
        } else {
            n = *(s32 *)(O + 0x148 + ((W(0x1B4) + i) % W(0x1B0)) * 4);
            h = n / 2;
            q = h / 4;
            r[2] = (n - 2 * h) * 256 + 0x100;
            r[0] = (n - 2 * h) * 256;
            r[1] = (h - 4 * q) * 64;
            r[3] = r[1] + 0x40;
            func_0026EC18(a0, sp10, q);
            func_0026EC48(a0, sp10, r);
            i++;
        }
    } while (i < 3);

    i = 0;
    off = 0;
    do {
        if (PC(0x280) + i < PC(0x21C)) {
            func_00325830(nm3, "mc_da4_cleamark_%d", i);
            func_0026EBC0(a0, nm3, sp10);
            g = (s32)D_00387F2C;
            c = *(s8 *)(g + func_0024B468(CUR) + PC(0x280) + i + 12);
            if (c != 0) {
                v = c - 1;
                h = v / 2;
                r[3] = h * 32 + 0x20;
                r[1] = h * 32;
                r[2] = (v - 2 * h) * 32 + 0x20;
                r[0] = (v - 2 * h) * 32;
                func_0026EC48(a0, sp10, r);
                func_0026EFC8(a0, sp10, 4);
            } else {
                func_0026EFC8(a0, sp10, 8);
            }
            if (W(0x134) & 0x10) {
                if (PC(0x280) + i == PC(0x1B8)) {
                    func_0026EBC0(a0, "mc_da3_on_plate", sp10);
                    func_0026EFC8(a0, sp10, 4);
                    func_0026EEC8(a0, sp10, 0, off);
                    func_0026F118(a0, sp10, &px, &py);
                    func_0026EBC0(a0, "mc_send", sp10);
                    func_0026EFC8(a0, sp10, 4);
                    func_0026EEC8(a0, sp10, 0, off);
                    func_0026EBC0(a0, "mc_dummy_number_on", sp10);
                    func_0024A6D8(a0, sp10, px, py, *(u8 **)(O + 0x18), PC(0x1B8) + 0xD0, 0,
                                  0xF0FFFF80, 0x40);
                    func_0026EBC0(a0, "mc_da4_dummy_text_on", sp10);
                    func_0041C8D8(a0, sp10, px + 6, py, *(u8 **)(O + 0x18), W(0x2E4) + PC(0x1B8), 0,
                                  0xFEE33280, 0x40);
                    i++;
                    off += 0x30;
                    continue;
                }
            } else {
                func_0026EBC0(a0, "mc_da3_on_plate", sp10);
                func_0026EFC8(a0, sp10, 8);
                func_0026EBC0(a0, "mc_send", sp10);
                func_0026EFC8(a0, sp10, 8);
            }
            func_00325830(nm3, "mc_da3_dummy_number_%d", i);
            func_0026EBC0(a0, nm3, sp10);
            func_0024A6D8(a0, sp10, 0, 0, *(u8 **)(O + 0x18), PC(0x280) + i + 0xD0, 0, 0x4C3C580,
                          0x2396440);
            func_00325830(nm3, "mc_da3_dummytext_%d", i);
            func_0026EBC0(a0, nm3, sp10);
            func_0041C8D8(a0, sp10, 6, 0, *(u8 **)(O + 0x18), W(0x2E4) + PC(0x280) + i, 0,
                          0xC8EAFD80, 0x40);
            i++;
        } else {
            func_00325830(nm3, "mc_da4_cleamark_%d", i);
            func_0026EBC0(a0, nm3, sp10);
            func_0026EFC8(a0, sp10, 8);
            i++;
        }
        off += 0x30;
    } while (i < 5);

    func_0026EBC0(a0, "mc_da_5_lv_csr", sp10);
    func_0026EEC8(a0, sp10, 56 * W(0x2E8), 0);
    r[3] = 0x40;
    r[1] = 0;
    r[0] = W(0x2E8) << 6;
    r[2] = (W(0x2E8) << 6) + 0x40;
    func_0026EBC0(a0, "mc_da_5_lv_number", sp10);
    func_0026EC48(a0, sp10, r);
    func_0026EBC0(a0, "mc_da5_csenario_plate", sp10);
    func_0026F118(a0, sp10, &qx, &qy);
    func_0026EBC0(a0, "mc_da5_dummy_number_on", sp10);
    func_0024A6D8(a0, sp10, qx, qy, *(u8 **)(O + 0x18), PC(0x1B8) + 0xD0, 0, 0xF0FFFF80, 0x40);
    func_0026EBC0(a0, "mc_da_5_dummy", sp10);
    func_0041C8D8(a0, sp10, qx + 6, qy, *(u8 **)(O + 0x18), W(0x2E4) + PC(0x1B8), 0, 0xFEE33280,
                  0x40);
    g = (s32)D_00387F2C;
    c = *(s8 *)(g + func_0024B468(CUR) + PC(0x1B8) + 12);
    func_0026EBC0(a0, "mc_da5_cleamark", sp10);
    if (c != 0) {
        v = c - 1;
        h = v / 2;
        r[3] = h * 32 + 0x20;
        r[1] = h * 32;
        r[2] = (v - 2 * h) * 32 + 0x20;
        r[0] = (v - 2 * h) * 32;
        func_0026EC48(a0, sp10, r);
        func_0026EFC8(a0, sp10, 4);
    } else {
        func_0026EFC8(a0, sp10, 8);
    }

    off = 0;
    i = 1;
    do {
        i--;
        func_0026EA58(O + off + 0x1C);
        off += 0x28;
    } while (i >= 0);
    func_0024C060();
}
