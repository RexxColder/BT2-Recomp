#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));

s32 func_1018B8(u8 *arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003F7710: G = D_0042A578, st = G->0x194. 1: G->0x148 = 0xF, st += 1, func_2493C0(0, 0x37A6, 0x3BBF, 0, 0xF).
 * 2: if func_1018B8(G) == 5: st += 1; else if (0x003B0C34 & 0x4000): st = 3 and func_297FE0(0, 1, 0x40, 0x40, 1).
 * 3: G->0x13C |= 3, G->0x18C = 0xF, st = 0. Others: nothing. */
void func_003F7710(void) {
    u8 *g;
    s32 st;

    g = D_0042A578;
    st = *(s32 *)(g + 0x194);

    if (st == 1) {
        *(s32 *)(g + 0x148) = 0xF;
        *(s32 *)(g + 0x194) = *(s32 *)(g + 0x194) + 1;
        func_2493C0(0, 0x37A6, 0x3BBF, 0, *(s32 *)(g + 0x148));
    } else if (st == 2) {
        if (func_1018B8(g) == 5) {
            *(s32 *)(g + 0x194) = *(s32 *)(g + 0x194) + 1;
        } else if (*(s32 *)0x003B0C34 & 0x4000) {
            *(s32 *)(g + 0x194) = 3;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
    } else if (st == 3) {
        *(s32 *)(g + 0x13C) = *(s32 *)(g + 0x13C) | 1;
        *(s32 *)(g + 0x13C) = *(s32 *)(g + 0x13C) | 2;
        *(s32 *)(g + 0x18C) = 0xF;
        *(s32 *)(g + 0x194) = 0;
    }
}
