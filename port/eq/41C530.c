#include "common.h"

extern u8 *D_0042FD70 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));

s32 func_26EB70(u8 *p);
void func_26EBA8(u8 *p, s32 a1);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_1018B8(void);
void EftShotFx_Update_2494A0(void);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x0041C530: state machine on G->0x88 (G = D_0042FD70), 25 states dispatched through jtbl_0042FE00 by (state-1) % 5:
 *   0: func_26EB70(G+0xC) & 8 -> state++;   1: func_2493C0(0,0x1FCF,0x33C5,0,G->0x7C), state++;
 *   2: func_1018B8() == 5 -> state++; else if D_003B0C34 & 0x4000: EftShotFx_Update_2494A0, state++, func_297FE0(0,1,0x40,0x40,1);
 *   3: func_26EBA8(G+0xC, 1), state++;   4: func_26EB70(G+0xC) & 0x200: if G->0x7C < 4 then G->0x7C++ and state++,
 *      else G->0x74 |= 3, G->0x80 = 0xF, state = 0. */
void func_0041C530(void) {
    s32 v;

    v = *(s32 *)(D_0042FD70 + 0x88);
    if (v == 0) {
        return;
    }
    v = v - 1;
    if ((u32)v >= 0x19) {
        return;
    }
    switch (v % 5) {
    case 0:
        if (func_26EB70(D_0042FD70 + 0xC) & 0x8) {
            *(s32 *)(D_0042FD70 + 0x88) += 1;
        }
        break;
    case 1:
        func_2493C0(0, 0x1FCF, 0x33C5, 0, *(s32 *)(D_0042FD70 + 0x7C));
        *(s32 *)(D_0042FD70 + 0x88) += 1;
        break;
    case 2:
        if (func_1018B8() == 5) {
            *(s32 *)(D_0042FD70 + 0x88) += 1;
        } else if (D_003B0C34 & 0x4000) {
            EftShotFx_Update_2494A0();
            *(s32 *)(D_0042FD70 + 0x88) += 1;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
        break;
    case 3:
        func_26EBA8(D_0042FD70 + 0xC, 1);
        *(s32 *)(D_0042FD70 + 0x88) += 1;
        break;
    case 4:
        if (func_26EB70(D_0042FD70 + 0xC) & 0x200) {
            if (*(s32 *)(D_0042FD70 + 0x7C) < 4) {
                *(s32 *)(D_0042FD70 + 0x7C) = *(s32 *)(D_0042FD70 + 0x7C) + 1;
                *(s32 *)(D_0042FD70 + 0x88) += 1;
            } else {
                *(s32 *)(D_0042FD70 + 0x74) |= 1;
                *(s32 *)(D_0042FD70 + 0x74) |= 2;
                *(s32 *)(D_0042FD70 + 0x80) = 0xF;
                *(s32 *)(D_0042FD70 + 0x88) = 0;
            }
        }
        break;
    }
}
