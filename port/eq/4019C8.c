#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_0042B968[] __attribute__((section(".data")));
extern u8 D_0042B978[] __attribute__((section(".data")));
extern u8 D_0042BB20[] __attribute__((section(".data")));

void BattleSetup_Finish(void);
s32 func_26EB70(u8 *p);
void func_26EBC0(u8 *a0, u8 *a1, s32 *a2);
void func_26ED60(u8 *a0, s32 *a1, s32 *a2, u8 *a3, s32 t0, f32 f12, f32 f13);
void func_24A598(u8 *a0, s32 *a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_26EA58(u8 *p);

/* 0x004019C8: menu draw step. b = G2 + 0xF4 (G2 = D_0042A590). Needs func_26EB70(b) & 1. Builds fr[4..7] = 0, 0,
 * 0x200, 0x80 and runs func_26EBC0 / func_26ED60 (18.0, 0.0) / func_26EBC0 / func_26ED60 (8.0, 0.0) / func_26EBC0 with
 * fr as the out block. Then the entry E = G2->0x274 + 56 * (P->0x64) (P = D_3876A4): when E->0xC is 2 or 4 two
 * func_24A598 calls with (E->0x14 + 1) and (E->0x18 + 1, a3 = 0x18), otherwise one call with a3 = 0xC; then func_26EA58(b)
 * and BattleSetup_Finish. */
void func_004019C8(void) {
    s32 fr[12];
    u8 *g2;
    u8 *b;
    u8 *e;
    s32 k;
    f32 zero;

    g2 = D_0042A590;
    b = g2 + 0xF4;
    if ((func_26EB70(b) & 1) == 0) {
        return;
    }
    fr[4] = 0;
    fr[5] = 0;
    fr[6] = 0x200;
    fr[7] = 0x80;
    func_26EBC0(b, D_0042B968, fr);
    zero = 0.0f;
    func_26ED60(b, fr, fr + 4, g2 + 0x25C, 0, 18.0f, zero);
    func_26EBC0(b, D_0042B978, fr);
    func_26ED60(b, fr, fr + 4, g2 + 0x260, 0, 8.0f, zero);
    func_26EBC0(b, D_0042BB20, fr);

    e = *(u8 **)(g2 + 0x274) + *(s32 *)(D_3876A4 + 0x64) * 56;
    k = *(s32 *)(e + 0xC);
    if (k == 2 || k == 4) {
        func_24A598(b, fr, 0, 0, *(s32 *)(g2 + 0x24), *(s32 *)(e + 0x14) + 1, 1);
        e = *(u8 **)(g2 + 0x274) + *(s32 *)(D_3876A4 + 0x64) * 56;
        func_24A598(b, fr, 0, 0x18, *(s32 *)(g2 + 0x24), *(s32 *)(e + 0x18) + 1, 1);
    } else {
        func_24A598(b, fr, 0, 0xC, *(s32 *)(g2 + 0x24), *(s32 *)(e + 0x14) + 1, 1);
    }
    func_26EA58(g2 + 0xF4);
    BattleSetup_Finish();
}
