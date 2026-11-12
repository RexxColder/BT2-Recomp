#include "common.h"

extern u8 *D_0042732C __attribute__((section(".data")));

void func_003DCAE0(s32 arg0);
void func_003DCF28(void);
void func_003DD100(u8 *a0);
void func_003DD160(void);
void func_003DDB20(void);
void func_003DDC88(void);
void func_003DDE30(s32 *a0);
void BattleSetup_Finish(void);
void BtlObjDraw_End(void);
void func_101890(void);
s32 func_105278(u8 *a0, s32 a1);
void func_2437E8(void);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
s32 func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
s32 func_26EB60(u8 *a0);
void func_2711A0(void);
void func_271240(void);
void func_277E70(s32 a0, s32 a1, s32 a2);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);

/* 0x003DE7C0: battle-result loop on P = D_0042732C (frame word fr[0] = 1, returned). Clears P->0x108 bit 0x40 when
 * the list at P->0x114 (count P->0x110) has no entry for which func_105278 returns nonzero. */
s32 func_003DE7C0(s32 arg0) {
    s32 fr[4];
    u8 *P;
    u8 *a0;
    s32 a1;
    s32 clear;

    fr[0] = 1;
    func_003DCAE0(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        BtlObjDraw_End();
        func_003DCF28();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003DDC88();
        func_003DD160();
        P = D_0042732C;
        if (*(s32 *)(P + 0x764) != 0) {
            func_003DDB20();
        }
        BattleSetup_Finish();
        func_277E70(*(s32 *)(P + 0x104), 0, (s32)(*(f32 *)(P + 0x76C) * 128.0f));

        P = D_0042732C;
        if (*(s32 *)(P + 0x108) & 0x40) {
            clear = 0;
            a1 = 0;
            a0 = *(u8 **)(P + 0x114);
            if (a0 == NULL) {
                clear = 1;
            } else {
                if (*(s32 *)(P + 0x110) > 0) {
                    a0 = *(u8 **)(a0 + 0x8);
                    for (;;) {
                        if (a0 == NULL) {
                            clear = 1;
                            break;
                        }
                        a1 += 1;
                        if (!(a1 < *(s32 *)(P + 0x110))) {
                            break;
                        }
                        a0 = *(u8 **)(a0 + 0x8);
                    }
                }
                if (!clear) {
                    if (a0 == NULL) {
                        clear = 1;
                    } else if (func_105278(*(u8 **)(a0 + 0x4), a1) != 0) {
                        clear = 1;
                    }
                }
            }
            if (clear) {
                P = D_0042732C;
                *(s32 *)(P + 0x108) = *(s32 *)(P + 0x108) & ~0x40;
            }
        }

        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0) {
            P = D_0042732C;
            if (*(s32 *)(P + 0x738) == 0 && func_26EB60(P + 0x2C) != 0) {
                *(s32 *)(P + 0x738) = 1;
                func_2493C0(*(s32 *)(P + 0x14), 0x3422, 0x383B, 0, *(s32 *)(P + 0x10C));
            }
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() != 0) {
            P = D_0042732C;
            if (*(s32 *)(P + 0x744) == 2) {
                if (*(s32 *)(P + 0x74C) == 4) {
                    func_003DD100(P);
                    func_28B218();
                    return fr[0];
                }
                continue;
            }
        }
        P = D_0042732C;
        if (*(s32 *)(P + 0x108) & 2) {
            *(s32 *)(P + 0x734) = *(s32 *)(P + 0x734) - 1;
            if (*(s32 *)(P + 0x734) == -1) {
                func_243A80(0, 0, 0);
            }
        } else {
            func_003DDE30(fr);
        }
    }
}
