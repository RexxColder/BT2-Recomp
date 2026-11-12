#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

void func_248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
void func_004120D0(s32 arg0);

void func_004121A8(void) {
    u8 *b;
    u8 *t;
    s32 k;
    s32 j;
    u32 fp;
    u32 sp0;
    u32 t3;
    u32 t4;
    u32 x;
    u32 y;
    u32 z;
    u32 w;
    u32 qv;
    u32 rv;
    u32 idx;
    u8 *pb;
    u32 v;

    b = D_0042BB7C;
    *(u8 **)(b + 0x2D8) = *(u8 **)(b + 4) + (*(u32 *)(*(u8 **)(b + 4) + 0x2C) & ~3u) + 4;
    *(u32 *)(b + 0x2D4) = *(u32 *)(*(u8 **)(b + 4) + (*(u32 *)(*(u8 **)(b + 4) + 0x2C) & ~3u));
    func_248708(b + 0x2E0, b + 0x2E4, b + 0x2D4, b + 0x2D8);

    b = D_0042BB7C;
    *(u32 *)(b + 0x2D4) = *(u32 *)(b + 0x2E0);
    *(u8 **)(b + 0x2D8) = b + 0x2E4;
    *(u8 **)(b + 0x2DC) = b + 0x1AF4;
    *(u32 *)(b + 0x3734) = (u32)((s32)*(u32 *)(b + 0x2D4) / 7);
    if ((s32)*(u32 *)(b + 0x2D4) % 7 != 0) {
        *(u32 *)(b + 0x3734) += 1;
    }
    *(u32 *)(b + 0x22C) = 0;

    b = D_0042BB7C;
    *(u32 *)(b + 0x230) = 0;
    *(u32 *)(b + 0x373C) = 1;
    *(u32 *)(b + 0x224) = 0;
    *(u32 *)(b + 0x228) = 0;
    *(u32 *)(b + 0x234) = 0;
    *(u32 *)(b + 0x230) |= 1u;

    for (k = 0; k < 2; k++) {
        fp = 134u * k;
        sp0 = 0x250u + 8u * k;
        t3 = 8u * k;
        t4 = 20u * k;

        for (j = 0; j < 2; j++) {
            b = D_0042BB7C;
            t = D_003876A4;

            *(u32 *)(t + t4 + 0x390) = (u32)k;
            *(u32 *)(t + t4 + 0x3B8) = 0;
            *(u32 *)(t + t4 + 0x408) = 0;
            *(u32 *)(t + t4 + 0x430) = 0;
            t4 += 4;

            x = *(u32 *)(t + 20 * k + 0x390);
            *(u32 *)(b + t3 + 0x230 + 0xC) = (u32)((s32)x % 7);
            *(u32 *)(b + t3 + 0x240 + 0xC) = (u32)((s32)x / 7);

            y = *(u32 *)(t + 20 * k + 0x408);
            *(u32 *)(b + t3 + 0x25C) = y;
            z = *(u32 *)(t + 20 * k + 0x3B8);
            *(u32 *)(b + t3 + 0x2B4) = z;
            w = *(u32 *)(t + 20 * k + 0x430);
            *(u32 *)(b + t3 + 0x2C4) = w;

            qv = *(u32 *)(b + 0xC + t3 + 0x240);
            rv = *(u32 *)(b + 0xC + t3 + 0x230);
            v = *(u32 *)(b + 0xC + sp0);
            idx = 7 * qv + fp + rv;
            *(u32 *)(b + 4 * idx + 0x3304) = v;

            pb = *(u8 **)(b + 4 * k + 0x2D8);
            idx = 7 * qv + rv;
            v = *(u32 *)(pb + 44 * idx);
            *(u32 *)(b + 0xC + t3 + 0x260) = v;

            t3 += 4;

            *(u32 *)(b + 4 * k + 0x284) = 0;
            *(u32 *)(b + 4 * k + 0x27C) = 0;
        }

        func_004120D0(k);
    }
}
