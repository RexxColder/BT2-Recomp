#include "common.h"

extern u8 *D_00421C00 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_00421C10[] __attribute__((section(".data")));
extern u8 D_00421C40[] __attribute__((section(".data")));

void *func_28BAA8(s32 arg0);
s32 func_100D58(u8 *arg0, s32 arg1, s32 arg2);
u8 *func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void func_29BB88(u8 *arg0, u8 *arg1);
s32 func_28A0B8(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* 0x003BB2A8: G = D_00421C00 = func_28BAA8(0x4450); memset(G, 0, 0x4450). If G->0 == 0: G->0 = func_100D58(0,0,0)
 * until nonzero, after func_100D58(*(D_003876A4+4) + 0x14, 0, 1). G->4 = func_2B24C8(G->0, 0, 0); G->8 = G->4 +
 * (G->4->8 & ~3); func_29BB88(G->4 + (G->4->4 & ~3), G->8); G->0x20 = -1; copy 0x2D bytes of D_00421C10 to G+0x348;
 * G->0x44C = 0x18; tail call func_28A0B8(G+0x30, D_00421C40, -1, -1, 1, 0x18). */
s32 func_003BB2A8(void) {
    u8 *g;
    u8 *p4;
    s32 v;

    g = (u8 *)func_28BAA8(0x4450);
    D_00421C00 = g;
    memset(g, 0, 0x4450);

    if (*(s32 *)g == 0) {
        func_100D58(*(u8 **)(D_003876A4 + 4) + 0x14, 0, 1);
        do {
            v = func_100D58(0, 0, 0);
            *(s32 *)D_00421C00 = v;
        } while (v == 0);
    }

    *(u8 **)(g + 4) = func_2B24C8(*(u8 **)g, 0, 0);
    p4 = *(u8 **)(g + 4);
    *(u8 **)(g + 8) = p4 + ((u32)*(s32 *)(p4 + 8) & ~3u);
    func_29BB88(*(u8 **)(g + 4) + ((u32)*(s32 *)(*(u8 **)(g + 4) + 4) & ~3u), *(u8 **)(g + 8));
    *(s32 *)(g + 0x20) = -1;
    memcpy(g + 0x348, D_00421C10, 0x2D);
    *(s32 *)(g + 0x44C) = 0x18;
    return func_28A0B8(g + 0x30, D_00421C40, -1, -1, 1, 0x18);
}
