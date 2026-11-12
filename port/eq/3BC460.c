#include "common.h"

extern u8 *D_00421C08 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void *func_28BAA8(s32 arg0);
void *memset(void *, int, unsigned int);
s32 func_100D58(s32 arg0, s32 arg1, s32 arg2);
u8 *func_2B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(void *arg0, u8 *arg1, u8 *arg2);

/* 0x003BC460: G = D_00421C08 = func_28BAA8(0x10), zeroed. If G->0 == 0: func_100D58(P->4 + 0x13, 0, 1) (P = D_3876A4) and
 * loop G->0 = func_100D58(0,0,0) until nonzero. Then G->4 = func_2B24C8(G->0, 0, 0); X = G->4 + (G->4->4 & ~3);
 * sp[0] = X; Res_RelocateOffsets(sp, X, X); G->8 = sp[0]; G->0xC = G->4 + (G->4->8 & ~3). */
void func_003BC460(void) {
    u8 *sp[2];
    u8 *g;
    s32 r;
    u8 *p4;

    D_00421C08 = (u8 *)func_28BAA8(0x10);
    memset(D_00421C08, 0, 0x10);

    if (*(s32 *)D_00421C08 == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 4) + 0x13, 0, 1);
        do {
            r = func_100D58(0, 0, 0);
            g = D_00421C08;
            *(s32 *)g = r;
        } while (r == 0);
    }

    g = D_00421C08;
    *(u8 **)(g + 4) = func_2B24C8(*(s32 *)g, 0, 0);

    g = D_00421C08;
    p4 = *(u8 **)(g + 4);
    sp[0] = p4 + ((u32)*(s32 *)(p4 + 4) & ~3u);
    Res_RelocateOffsets(sp, sp[0], sp[0]);

    g = D_00421C08;
    *(u8 **)(g + 8) = sp[0];

    g = D_00421C08;
    p4 = *(u8 **)(g + 4);
    *(u8 **)(g + 0xC) = p4 + ((u32)*(s32 *)(p4 + 8) & ~3u);
}
