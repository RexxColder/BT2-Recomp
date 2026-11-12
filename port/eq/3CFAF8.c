#include "common.h"

extern u8 *D_0042311C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 ColorFade_IsFadingOut(void);
s32 ColorFade_IsInDone(void);
s32 ColorFade_IsOutDone(void);
void func_003CDF80(s32 arg0);
void func_003CE990(u8 *g);
void func_003CEA08(void);
void func_003CEDD0(s32 *out);
void func_003CED48(void);
void func_003CEF10(void);
void func_101890(void);
void func_2437E8(void);
void func_2438E8(void);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
s32 func_26EB60(u8 *p);
void func_2711A0(void);
void func_271240(void);
void func_28B090(void);
void func_28B218(void);
void func_28BDA0(void);
void func_297978(void);

/* 0x003CFAF8: sibling of 0x3E09A0 on D = D_0042311C (0x128 armed flag: G->0x11C = G->0x120 and func_2493C0(G->8,
 * 0x342E, 0x3847, 0, G->0x11C); 0x118 bit 2, 0x150 gate, 0x124 countdown; on -1 clears P->0x18 bits 0x10 and 0x20 and
 * sets P->0x88 = 0, with P = D_3876A4). */
s32 func_003CFAF8(s32 arg0) {
    s32 sp[4];
    s32 v;

    sp[0] = 1;
    func_003CDF80(arg0);
    func_243968(0, 0, 0);
    for (;;) {
        func_2711A0();
        func_28B090();
        func_28BDA0();
        func_297978();
        func_2438E8();
        func_003CED48();
        func_003CEA08();
        BattleSetup_Finish();
        func_003CEF10();
        func_2437E8();
        func_271240();
        if (ColorFade_IsInDone() != 0 && *(s32 *)(D_0042311C + 0x128) == 0 &&
            func_26EB60(D_0042311C + 0x8C) != 0) {
            *(s32 *)(D_0042311C + 0x128) = 1;
            *(s32 *)(D_0042311C + 0x11C) = *(s32 *)(D_0042311C + 0x120);
            func_2493C0(*(s32 *)(D_0042311C + 0x8), 0x342E, 0x3847, 0, *(s32 *)(D_0042311C + 0x11C));
        }
        if (ColorFade_IsFadingOut() != 0) {
            func_101890();
            continue;
        }
        if (ColorFade_IsOutDone() == 0) {
            if (!(*(s32 *)(D_0042311C + 0x118) & 2)) {
                if (*(s32 *)(D_0042311C + 0x150) == 0) {
                    func_003CEDD0(sp);
                }
            } else {
                v = *(s32 *)(D_0042311C + 0x124) - 1;
                *(s32 *)(D_0042311C + 0x124) = v;
                if (v == -1) {
                    func_243A80(0, 0, 0);
                    *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) & ~0x10;
                    *(s32 *)(D_3876A4 + 0x18) = *(s32 *)(D_3876A4 + 0x18) & ~0x20;
                    *(s32 *)(D_3876A4 + 0x88) = 0;
                }
            }
            continue;
        }
        break;
    }
    func_003CE990(D_0042311C);
    func_28B218();
    return sp[0];
}
