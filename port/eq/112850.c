#include "common.h"

extern u8 D_0036C958[];
void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *arg0, s32 arg1);
void Dma_AddRef(s32 arg0, s32 arg1);

s32 func_00112850(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *p;
    u8 *base;
    u8 *rec;
    u8 tpl[48];
    s32 idx;
    s32 n;
    s32 s3;

    p = (u8 *)arg0;
    base = (u8 *)*(s32 *)(p + 0x10);
    memcpy(tpl, D_0036C958, 48);

    idx = arg1;
    rec = base + idx * 64;
    if (*(s32 *)(rec + 0x28) != 0) {
        return *(s32 *)(rec + 0x28);
    }
    *(s32 *)(rec + 0x28) = 1;

    if (*(s32 *)(rec + 0x8) != 0) {
        *(s32 *)(tpl + 0x20) = 0;
        *(s32 *)(tpl + 0x24) = (*(s32 *)(rec + 0x20) + arg2) | ((*(u32 *)(rec + 0x18) & 0xFFFF) << 16);
        Dma_AddData(tpl, 48);
        Dma_AddRef(*(s32 *)(rec + 0x38), *(s32 *)(rec + 0x8));
    }
    if (*(s32 *)(rec + 0xC) != 0) {
        *(s32 *)(tpl + 0x20) = 0;
        *(s32 *)(tpl + 0x24) = (*(s32 *)(rec + 0x24) + arg3) | ((*(u32 *)(rec + 0x1C) & 0xFFFF) << 16);
        Dma_AddData(tpl, 48);
        Dma_AddRef(*(s32 *)(rec + 0x3C), *(s32 *)(rec + 0xC));
    }

    s3 = 0;
    for (;;) {
        n = *(s32 *)p;
        idx = idx + 1;
        if ((u32)idx >= (u32)n) {
            return 0;
        }
        rec = base + idx * 64;
        if (*(s32 *)(rec + 0x28) != 0) {
            return *(s32 *)(rec + 0x28);
        }
        if (*(s32 *)(rec + 0x8) != 0) {
            return *(s32 *)(rec + 0x8);
        }
        if (*(s32 *)(rec + 0xC) != 0) {
            *(s32 *)(tpl + 0x20) = 0;
            *(s32 *)(tpl + 0x24) = (*(s32 *)(rec + 0x24) + arg3) | ((*(u32 *)(rec + 0x1C) & 0xFFFF) << 16);
            Dma_AddData(tpl, 48);
            Dma_AddRef(*(s32 *)(rec + 0x3C), *(s32 *)(rec + 0xC));
        }
        s3 = s3 + 1;
        *(s32 *)(rec + 0x28) = 1;
        if (s3 >= 6) {
            break;
        }
    }
    return (s32)rec;
}
