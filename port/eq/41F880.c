#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_0041CD90(void);
s32 func_0041CF48(s32 arg0);
void func_0041DB28(void);
void func_0041DBB0(void);
void func_0041E928(void);
void func_0041F138(void);
void func_0041F198(u8 *a0);
void func_101490(void);
void func_101498(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
s32 func_26EB60(u8 *a0);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x0041F880: menu frame loop on P = D_0042FD74 until ColorFade reports out-done. The frame word fr[0] starts at 1
 * and is the return value; when it is set on exit, G = D_3876A4 gets the P-table words (0x30, 0x34, 0x38) and the
 * bit (1 << P->0x148[P->0x1AC]) is set in G->0x2C (or G->0x18 |= 0x200 when it was already set). */
s32 func_0041F880(s32 arg0) {
    u8 fr[0x10];
    u8 *P;
    u8 *G;
    u8 *a0;
    s32 i;
    s32 mask;
    s32 v;

    *(s32 *)fr = 1;
    func_0041CF48(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_0041CD90();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_0041E928();
        func_0041F138();
        func_0041DBB0();
        BattleSetup_Finish();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            P = D_0042FD74;
            if (*(s32 *)(P + 0x2FC) == 0 && func_26EB60(P + 0x44) != 0) {
                *(s32 *)(P + 0x2FC) = 1;
                *(s32 *)(P + 0x300) = 1;
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            func_101498();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            P = D_0042FD74;
            if ((*(s32 *)(P + 0x134) & 2) == 0) {
                if (*(s32 *)(P + 0x300) == 0) {
                    func_0041F198(fr);
                }
            } else {
                v = *(s32 *)(P + 0x2F8) - 1;
                *(s32 *)(P + 0x2F8) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                }
            }
            continue;
        }
        if (*(s32 *)fr != 0) {
            P = D_0042FD74;
            G = D_3876A4;
            i = *(s32 *)(P + 0x1AC);
            *(s32 *)(G + 0x30) = *(s32 *)(P + i * 4 + 0x148);
            a0 = P + 0x8;
            *(s32 *)(G + 0x34) = *(s32 *)(a0 + *(s32 *)(a0 + i * 4 + 0x140) * 4 + 0x1B0);
            *(s32 *)(G + 0x38) = *(s32 *)(P + 0x2E8);
            mask = 1 << (*(s32 *)(P + i * 4 + 0x148) & 31);
            if ((*(s32 *)(G + 0x2C) & mask) == 0) {
                *(s32 *)(G + 0x2C) = *(s32 *)(G + 0x2C) | mask;
            } else {
                *(s32 *)(G + 0x18) = *(s32 *)(G + 0x18) | 0x200;
            }
        }
        func_0041DB28();
        func_28B218();
        return *(s32 *)fr;
    }
}
