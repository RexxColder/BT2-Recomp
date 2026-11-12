#include "common.h"

void Dma_SendGif(s64 *arg0, s32 arg1, s64 arg2, s64 arg3, s64 arg4, s64 arg5, s64 arg6, s64 arg7);
void func_0028C760(void);
void *memset(void *s, s32 c, u32 n);
extern s64 D_00376908[] __attribute__((section(".data")));
extern u8 gGfx[] __attribute__((section(".data")));

void func_00270FF0(void) {
    s64 sp[8];

    sp[0] = D_00376908[0];
    sp[1] = D_00376908[1];
    sp[2] = D_00376908[2];
    sp[3] = D_00376908[3];
    sp[4] = D_00376908[4];
    sp[5] = D_00376908[5];
    sp[6] = D_00376908[6];
    sp[7] = D_00376908[7];
    Dma_SendGif(sp, 4, D_00376908[1], D_00376908[2], D_00376908[3], D_00376908[4], D_00376908[5], D_00376908[6]);
    memset(gGfx, 0, 0x250);
    func_0028C760();
}
