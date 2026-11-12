#include "common.h"

extern u8 *D_0042A578 __attribute__((section(".data")));

void func_26EA88(u8 *arg0);
void func_003F5750(s32 arg0, u8 *arg1, u8 *arg2);

/* 0x003F5D40: calls func_26EA88(G+0x38) (G = D_0042A578), then with R = G[4*G->0x140 + 0x14C] and base = G->0x1C4:
 * G->0x19C = base[56*R+8] - 1; G->0x1A0 = G->0x19C - 1; G->0x1A4 = base[56*R'+8] + 1 (R' from the same chain);
 * G->0x1A8 = base[56*R''+8] + 2; then tail-calls func_003F5750(R'', base, G). Each step reloads G. */
void func_003F5D40(void) {
    u8 *g;
    u8 *base;
    s32 r;
    s32 w;

    func_26EA88(D_0042A578 + 0x38);

    g = D_0042A578;
    base = *(u8 **)(g + 0x1C4);
    r = *(s32 *)(g + *(s32 *)(g + 0x140) * 4 + 0x14C);
    w = *(s32 *)(base + r * 0x38 + 8);
    *(s32 *)(g + 0x19C) = w - 1;
    *(s32 *)(g + 0x1A0) = *(s32 *)(g + 0x19C) - 1;

    g = D_0042A578;
    base = *(u8 **)(g + 0x1C4);
    r = *(s32 *)(g + *(s32 *)(g + 0x140) * 4 + 0x14C);
    w = *(s32 *)(base + r * 0x38 + 8);
    *(s32 *)(g + 0x1A4) = w + 1;

    g = D_0042A578;
    base = *(u8 **)(g + 0x1C4);
    r = *(s32 *)(g + *(s32 *)(g + 0x140) * 4 + 0x14C);
    w = *(s32 *)(base + r * 0x38 + 8);
    *(s32 *)(g + 0x1A8) = w + 2;

    func_003F5750(r, base, g);
}
