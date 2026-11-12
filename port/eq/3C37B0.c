#include "common.h"

extern u8 *D_00421CF4 __attribute__((section(".data")));
extern u8 D_00422CC0 __attribute__((section(".data")));

s32 func_26EB70(u8 *arg0);
void func_26EBC0(u8 *arg0, u8 *arg1, s32 *arg2);
void func_26EC48(u8 *arg0, s32 *arg1, s32 *arg2);
void func_26E9E8(u8 *arg0);

/* 0x003C37B0: G = D_00421CF4. If G->0x680 > 0 it is decremented. If func_26EB70(G+0x60) has bit 0x200: frame[4] = 0,
 * frame[5] = (G->0x1FC & 8) ? 0 : 0x20, frame[6] = frame[4] + 0x200, frame[7] = frame[5] + 0x20, then
 * func_26EBC0(G+0x60, &D_00422CC0, frame) and func_26EC48(G+0x60, frame, &frame[4]). Finally func_26E9E8(G+0x28*j+0x38)
 * for j = 0..2. */
void func_003C37B0(void) {
    s32 frame[8];
    s32 j;

    if (*(s32 *)(D_00421CF4 + 0x680) > 0) {
        *(s32 *)(D_00421CF4 + 0x680) = *(s32 *)(D_00421CF4 + 0x680) - 1;
    }

    if (func_26EB70(D_00421CF4 + 0x60) & 0x200) {
        frame[4] = 0;
        if (*(s32 *)(D_00421CF4 + 0x1FC) & 8) {
            frame[5] = 0;
        } else {
            frame[5] = 0x20;
        }
        frame[6] = frame[4] + 0x200;
        frame[7] = frame[5] + 0x20;
        func_26EBC0(D_00421CF4 + 0x60, &D_00422CC0, frame);
        func_26EC48(D_00421CF4 + 0x60, frame, &frame[4]);
    }

    for (j = 0; j < 3; j++) {
        func_26E9E8(D_00421CF4 + j * 0x28 + 0x38);
    }
}
