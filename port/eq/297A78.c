#include "common.h"

extern u8 *D_00387ED0;
extern u8 *D_003876A0;
extern s32 D_003B0E00[] __attribute__((section(".data")));

s32 func_00100CB8(s32 arg0);
s32 func_0028BC68(s32 arg0);
void Dma_SendToIop(s32 arg0, s32 arg1, s32 arg2);
s32 sceSdRemote(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 sceSifAllocIopHeap(s32 arg0, u8 *arg1);
void func_00297640(u8 *arg0, s32 *arg1);
void func_0028BB60(s32 arg0);

void func_00297A78(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s1;
    u8 *g;
    u8 *h;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 a0v;
    s32 v0;
    s32 v1;

    s1 = (u8 *)arg1;
    if (arg1 == 0) {
        s1 = (u8 *)func_00100CB8(arg0);
    }
    g = D_00387ED0;
    h = D_003876A0;

    /* block 1: the transfer size for the first DMA (s2) */
    if (*(s32 *)(g + 0x60) == 2) {
        s2 = 0x13800;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto l918;
        }
        v0 = *(s32 *)(g + 0x60) - 3;
    } else {
        v0 = *(s32 *)(g + 0x60) - 3;
    }
    if ((u32)v0 < 2U) {
        s2 = 0x73000;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto l918;
        }
        v1 = *(s32 *)(s1 + 0x8);
    } else {
        v1 = *(s32 *)(s1 + 0x8);
    }
    s2 = v1 - *(s32 *)(s1 + 0x4);

l918:
    s3 = func_0028BC68(s2);
    s0 = *(s32 *)(g + 0x6C);
    Dma_SendToIop(s0, (s32)(s1 + ((((u32)*(s32 *)(s1 + 0x4)) >> 2) << 2)),
                  *(s32 *)(s1 + 0x8) - *(s32 *)(s1 + 0x4));
    sceSdRemote(1, 0x80D0, 1, 0, s0, s3, s2);
    if (arg2 != 0) {
        /* the asm sets only four argument registers for this call */
        ((s32 (*)(s32, s32, s32, s32))sceSdRemote)(1, 0x80F0, 1, 1);
    }
    *(s32 *)(g + (*(s32 *)(g + 0x60) << 2)) = s3;

    /* block 2: second DMA, buffer at +0x20 */
    if (*(s32 *)(g + 0x60) == 2) {
        a0v = 0x800;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto l9f4;
        }
        v0 = *(s32 *)(g + 0x60) - 3;
    } else {
        v0 = *(s32 *)(g + 0x60) - 3;
    }
    if ((u32)v0 < 2U) {
        a0v = 0x1000;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto l9f4;
        }
        v1 = *(s32 *)(s1 + 0xC);
    } else {
        v1 = *(s32 *)(s1 + 0xC);
    }
    a0v = v1 - *(s32 *)(s1 + 0x8);

l9f4:
    s0 = sceSifAllocIopHeap(a0v, g);
    Dma_SendToIop(s0, (s32)(s1 + ((((u32)*(s32 *)(s1 + 0x8)) >> 2) << 2)),
                  *(s32 *)(s1 + 0xC) - *(s32 *)(s1 + 0x8));
    *(s32 *)(g + (*(s32 *)(g + 0x60) << 2) + 0x20) = s0;

    /* block 3: third DMA, buffer at +0x40 */
    if (*(s32 *)(g + 0x60) == 2) {
        a0v = 0x800;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto lc90;
        }
        v0 = *(s32 *)(g + 0x60) - 3;
    } else {
        v0 = *(s32 *)(g + 0x60) - 3;
    }
    if ((u32)v0 < 2U) {
        a0v = 0x800;
        if ((*(s64 *)(h + 0x4D8) & 0xB) != 0) {
            goto lc90;
        }
        v1 = *(s32 *)(s1 + 0x10);
    } else {
        v1 = *(s32 *)(s1 + 0x10);
    }
    a0v = v1 - *(s32 *)(s1 + 0xC);

lc90:
    s0 = sceSifAllocIopHeap(a0v, g);
    Dma_SendToIop(s0, (s32)(s1 + ((((u32)*(s32 *)(s1 + 0xC)) >> 2) << 2)),
                  *(s32 *)(s1 + 0x10) - *(s32 *)(s1 + 0xC));
    *(s32 *)(g + (*(s32 *)(g + 0x60) << 2) + 0x40) = s0;
    D_003B0E00[0] = s3;
    D_003B0E00[1] = *(s32 *)(g + (*(s32 *)(g + 0x60) << 2) + 0x20);
    D_003B0E00[2] = *(s32 *)(g + (*(s32 *)(g + 0x60) << 2) + 0x40);
    func_00297640(g, D_003B0E00);

    if (arg1 == 0) {
        func_0028BB60((s32)s1);
    }
    *(s32 *)(g + 0x60) = *(s32 *)(g + 0x60) + 1;
}
