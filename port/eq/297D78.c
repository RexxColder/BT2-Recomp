#include "common.h"

void Dma_SendToIop(s32 arg0, s32 arg1, s32 arg2);
s32 sceSdRemote(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2);
void func_00297660(s32 arg0, s32 arg1);
extern u8 *D_00387ED0;
extern u8 D_003B0E00[] __attribute__((section(".data")));

s32 func_00297D78(s32 arg0, u8 *arg1) {
    s32 v3;
    s32 s4;
    s32 s5;
    s32 s2;
    s32 s1;
    s32 s0;
    s32 t;
    u32 v0;
    u32 a2;
    u32 a2b;

    v3 = arg0 * 4;
    s4 = v3 + 0x20;
    s5 = v3 + 0x40;
    if (*(s32 *)(D_00387ED0 + 0x70) == 0) {
        v0 = *(u32 *)(arg1 + 4);
        s2 = *(s32 *)(D_00387ED0 + v3);
        s0 = (s32)(*(u32 *)(arg1 + 8) - v0);
        s1 = *(s32 *)(D_00387ED0 + 0x6C);
        Dma_SendToIop(s1, (s32)(arg1 + ((v0 >> 2) * 4)), s0);
        sceSdRemote(1, 0x80D0, 1, 0, s1, s2, s0);
        a2 = *(u32 *)(arg1 + 8);
        Dma_SendToIop(*(s32 *)(D_00387ED0 + s4), (s32)(arg1 + ((a2 >> 2) * 4)),
                      (s32)(*(u32 *)(arg1 + 0xC) - a2));
        a2b = *(u32 *)(arg1 + 0xC);
        Dma_SendToIop(*(s32 *)(D_00387ED0 + s5), (s32)(arg1 + ((a2b >> 2) * 4)),
                      (s32)(*(s32 *)(arg1 + 0x10) - a2b));
        *(s32 *)(D_003B0E00 + 0) = s2;
        *(s32 *)(D_003B0E00 + 4) = *(s32 *)(D_00387ED0 + s4);
        t = *(s32 *)(D_00387ED0 + s5);
        *(s32 *)(D_003B0E00 + 0xC) = arg0;
        *(s32 *)(D_003B0E00 + 8) = t;
        func_00297660((s32)D_003B0E00, t);
        *(s32 *)(D_00387ED0 + 0x70) = 1;
    }
    return 1;
}
