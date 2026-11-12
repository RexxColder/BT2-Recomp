#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));

void func_29BD28(void);
void func_26E908(u8 *arg0);
void func_28BB60(u8 *arg0);

/* 0x00413C48: func_29BD28(); for j in 0..5: func_26E908(G + 0x28*j + 0x38) (G = D_0042BB7C, reloaded each call).
 * Then func_28BB60(G->0x28); for j in 0..1 (s0 = 8*j): twice { func_28BB60(G->[s0+8]); func_28BB60(G->[s0+0x18]);
 * s0 += 4 }. Finally func_28BB60(G->4) and tail func_28BB60(G). */
void func_00413C48(void) {
    s32 j;
    s32 k;
    s32 s0;

    func_29BD28();
    for (j = 0; j < 6; j++) {
        func_26E908(D_0042BB7C + j * 0x28 + 0x38);
    }

    func_28BB60(*(u8 **)(D_0042BB7C + 0x28));

    for (j = 0; j < 2; j++) {
        s0 = j * 8;
        for (k = 0; k < 2; k++) {
            func_28BB60(*(u8 **)(D_0042BB7C + s0 + 8));
            func_28BB60(*(u8 **)(D_0042BB7C + s0 + 0x18));
            s0 += 4;
        }
    }

    func_28BB60(*(u8 **)(D_0042BB7C + 4));
    func_28BB60(D_0042BB7C);
}
