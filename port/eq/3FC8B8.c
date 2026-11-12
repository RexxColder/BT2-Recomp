#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));
extern u8 D_0042B6C8[] __attribute__((section(".data")));
extern u8 D_0042B6D8[] __attribute__((section(".data")));
extern u8 D_0042B6E8[] __attribute__((section(".data")));
extern u8 D_0042B6F8[] __attribute__((section(".data")));
extern u8 D_0042B710[] __attribute__((section(".data")));
extern u8 D_0042B728[] __attribute__((section(".data")));
extern u8 D_0042B738[] __attribute__((section(".data")));
extern u8 D_0042B748[] __attribute__((section(".data")));
extern u8 D_0042B760[] __attribute__((section(".data")));
extern u8 D_0042B770[] __attribute__((section(".data")));
extern u8 D_0042B780[] __attribute__((section(".data")));
extern u8 D_0042B790[] __attribute__((section(".data")));
extern u8 D_0042B7A0[] __attribute__((section(".data")));
extern u8 D_0042B7B0[] __attribute__((section(".data")));
extern u8 D_0042B7C8[] __attribute__((section(".data")));
extern u8 D_0042B7E0[] __attribute__((section(".data")));
extern u8 D_0042B7F8[] __attribute__((section(".data")));
extern u8 D_0042B810[] __attribute__((section(".data")));
extern u8 D_0042B828[] __attribute__((section(".data")));
extern u8 D_0042B830[] __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
void func_00325830();
void func_0026EBC0(void *a0, void *a1, void *a2);
void func_0026EC48(void *a0, void *a1, void *a2);
void func_0026EFC8(void *a0, void *a1, s32 a2);
void func_0026EA58(void *a0);
void Num_ToDigits(u8 *digits, s32 value, s32 count, s32 zeroPad);
void Num_DrawDigits(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, u8 *arg4, u8 *arg5);
s32 func_0024A8A0(s8 *buf, s32 a1, s32 a2);
void func_003FB620(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, u8 *arg6);
void func_00249A98(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00249778(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3);

#define DW(off) (*(s32 *)(D_0042A588 + (off)))
#define W(off) (*(s32 *)(sp + (off)))
#define R(off) ((void *)(sp + (off)))

/* tail of the loop: refs of an N-digit field (name fmt with index a2), then digits */
s32 func_003FC8B8(void) {
    u8 sp[0x220];
    u8 *s4;
    s32 i;
    s32 j;

    func_00277E70(*(u8 **)(D_0042A588 + 0x88), 0, 0x80);
    s4 = D_0042A588 + 0x60;
    func_0026EBC0(s4, D_0042B6C8, R(0));
    func_0026EFC8(s4, R(0), 8);
    func_0026EBC0(s4, D_0042B6D8, R(0));
    func_0026EFC8(s4, R(0), DW(0x230) == 0 ? 8 : 4);
    W(0x10) = 0x20;
    W(0x18) = 0x40;
    W(0x1C) = 0x20;
    W(0x14) = 0;
    func_0026EBC0(s4, D_0042B6E8, R(0));
    func_0026EC48(s4, R(0), R(0x10));
    func_0026EFC8(s4, R(0), ((DW(0x230) + 5) < DW(0x22C)) ? 4 : 8);

    /* mc_estimation_text_%d */
    for (i = 0; i < 4; i++) {
        func_00325830(R(0x30), D_0042B6F8, i);
        func_0026EBC0(s4, R(0x30), R(0));
        W(0x14) = i << 5;
        W(0x1C) = (i << 5) + 0x20;
        W(0x10) = 0;
        W(0x18) = 0x100;
        func_0026EC48(s4, R(0), R(0x10));
    }
    /* mc_point_text_%d */
    for (i = 0; i < 2; i++) {
        func_00325830(R(0x50), D_0042B710, i);
        func_0026EBC0(s4, R(0x50), R(0));
        W(0x14) = i << 5;
        W(0x1C) = (i << 5) + 0x20;
        W(0x10) = 0;
        W(0x18) = 0x100;
        func_0026EC48(s4, R(0), R(0x10));
    }
    /* mc_rank_%d */
    for (i = 0; i < 4; i++) {
        s32 *p;
        s32 v;
        func_00325830(R(0x70), D_0042B728, i + 1);
        func_0026EBC0(s4, R(0x70), R(0));
        p = (s32 *)(D_0042A588 + (i << 2) + 0x13C);
        v = ((*p) / 3) << 5;
        W(0x14) = v;
        W(0x1C) = v + 0x20;
        v = ((*p) % 3) << 5;
        W(0x10) = v;
        W(0x18) = v + 0x20;
        func_0026EC48(s4, R(0), R(0x10));
    }
    /* mc_general_rank */
    {
        s32 v = (DW(0x14C) / 3) << 6;
        W(0x14) = v;
        W(0x1C) = v + 0x40;
        v = (DW(0x14C) % 3) << 6;
        W(0x10) = v;
        W(0x18) = v + 0x40;
        func_0026EBC0(s4, D_0042B738, R(0));
        func_0026EC48(s4, R(0), R(0x10));
    }
    /* mc_percentage_%d */
    for (i = 0; i < 3; i++) {
        func_00325830(R(0x90), D_0042B748, 2 - i);
        func_0026EBC0(s4, R(0x90), R(0xB0 + 8 * i));
    }
    Num_ToDigits(R(0xD0), DW(0x124), 3, 1);
    Num_DrawDigits(s4, R(0xB0), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0xD0));
    /* mc_time_%d */
    for (i = 0; i < 5; i++) {
        func_00325830(R(0x90), D_0042B760, 4 - i);
        func_0026EBC0(s4, R(0x90), R(0xE0 + 8 * i));
    }
    Num_ToDigits(R(0x110), DW(0x128), 5, 1);
    Num_DrawDigits(s4, R(0xE0), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x110));
    /* mc_maxhit_%d */
    for (i = 0; i < 2; i++) {
        func_00325830(R(0x90), D_0042B770, 1 - i);
        func_0026EBC0(s4, R(0x90), R(0x120 + 8 * i));
    }
    Num_ToDigits(R(0x130), DW(0x12C), 2, 1);
    Num_DrawDigits(s4, R(0x120), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x130));
    /* mc_maxdamage_%d */
    for (i = 0; i < 5; i++) {
        func_00325830(R(0x90), D_0042B780, 4 - i);
        func_0026EBC0(s4, R(0x90), R(0x140 + 8 * i));
    }
    Num_ToDigits(R(0x170), DW(0x130), 5, 1);
    Num_DrawDigits(s4, R(0x140), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x170));
    /* mc_b_point_%d */
    for (i = 0; i < 8; i++) {
        func_00325830(R(0x90), D_0042B790, 7 - i);
        func_0026EBC0(s4, R(0x90), R(0xB0 + 8 * i));
    }
    func_0024A8A0(R(0xF0), DW(0x184), 8);
    Num_DrawDigits(s4, R(0xB0), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0xF0));
    /* mc_c_point_%d */
    for (i = 0; i < 8; i++) {
        func_00325830(R(0x90), D_0042B7A0, 7 - i);
        func_0026EBC0(s4, R(0x90), R(0xB0 + 8 * i));
    }
    func_0024A8A0(R(0xF0), 100 * *(s32 *)(D_003876A4 + 0x60) + DW(0x184), 8);
    Num_DrawDigits(s4, R(0xB0), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0xF0));
    /* mc_estimation_%d_%d */
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            func_00325830(R(0x100), D_0042B7B0, i, 4 - j);
            func_0026EBC0(s4, R(0x100), R(0x180 + 8 * j));
        }
        func_0024A8A0(R(0x120), *(s32 *)(D_0042A588 + 0x168 + 4 * i + 4), 5);
        Num_DrawDigits(s4, R(0x180), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x120));
    }
    /* mc_general_point_%d */
    for (i = 0; i < 5; i++) {
        func_00325830(R(0x100), D_0042B7C8, 4 - i);
        func_0026EBC0(s4, R(0x100), R(0x180 + 8 * i));
    }
    func_0024A8A0(R(0x120), DW(0x17C), 5);
    Num_DrawDigits(s4, R(0x180), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x120));
    /* mc_bonus_point_%d */
    for (i = 0; i < 5; i++) {
        func_00325830(R(0x100), D_0042B7E0, 4 - i);
        func_0026EBC0(s4, R(0x100), R(0x180 + 8 * i));
    }
    func_0024A8A0(R(0x120), DW(0x180), 5);
    Num_DrawDigits(s4, R(0x180), 0, 0, *(u8 **)(D_0042A588 + 0x268), R(0x120));
    /* mc_dummy_text_%d */
    for (i = 0; i < 5; i++) {
        if (DW(0x230) + i < DW(0x22C)) {
            func_00325830(R(0x1B0), D_0042B7F8, i);
            func_0026EBC0(s4, R(0x1B0), R(0));
            func_003FB620((s32)s4, R(0), 0, 0, *(u8 **)(D_0042A588 + 0xC),
                          DW(0x188 + 4 * (DW(0x230) + i)) + 0x61, 0);
        }
    }
    /* mc_dummy_point_%d */
    for (i = 0; i < 5; i++) {
        if (DW(0x230) + i < DW(0x22C)) {
            s32 v;
            func_00325830(R(0x1B0), D_0042B810, i);
            func_0026EBC0(s4, R(0x1B0), R(0));
            v = *(s32 *)(*(u8 **)(D_0042A588 + 0x25C) + 4 * DW(0x188 + 4 * (DW(0x230) + i)));
            func_00249A98((s32)s4, R(0), 0, 0, 100 * v, 2);
        }
    }
    s4 = D_0042A588 + 0x10;
    func_0026EBC0(s4, D_0042B828, R(0));
    func_0026EFC8(s4, R(0), 0x80);
    s4 = D_0042A588 + 0x38;
    func_0026EBC0(s4, D_0042B830, R(0));
    func_00249778((s32)s4, R(0), (s32 *)(D_0042A588 + 0x11C), 1);
    for (i = 0; i < 3; i++) {
        func_0026EA58(D_0042A588 + 0x28 * i + 0x10);
    }
    return 0x430000;
}
