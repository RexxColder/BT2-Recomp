#include "common.h"

extern u8 D_00376F90[] __attribute__((section(".data")));

void Dma_AddData(u8 *arg0, s32 arg1);
void Dma_AddRef(s32 arg0, s32 arg1);

void func_002869B0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 buf[48];
    s32 count;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 s5;
    s32 s6;
    u8 *base;
    u8 *rec;
    s32 hi;

    s5 = arg1;
    s6 = arg2;
    s4 = arg3;
    s3 = arg4;
    count = *(s32 *)arg0;
    memcpy(buf, D_00376F90, 48);
    if (count == 0) {
        return;
    }
    base = *(u8 **)(arg0 + 0x10);
    s1 = 0;
    s2 = 0;
    do {
        if (s2 >= s5 && (s2 < s5 + s6)) {
            rec = base + s1;
            hi = s4 | (s32)((*(u32 *)(rec + 0x18) & 0xFFFF) << 16);
            *(s32 *)(buf + 0x20) = 0;
            *(s32 *)(buf + 0x24) = hi;
            Dma_AddData(buf, 0x30);
            Dma_AddRef(*(s32 *)(base + s1 + 0x38), *(s32 *)(base + s1 + 0x8));

            rec = base + s1;
            hi = s3 | (s32)((*(u32 *)(rec + 0x1C) & 0xFFFF) << 16);
            *(s32 *)(buf + 0x20) = 0;
            *(s32 *)(buf + 0x24) = hi;
            Dma_AddData(buf, 0x30);
            Dma_AddRef(*(s32 *)(base + s1 + 0x3C), *(s32 *)(base + s1 + 0xC));

            count = *(s32 *)arg0;
            base = *(u8 **)(arg0 + 0x10);
        }
        rec = base + s1;
        s1 += 0x40;
        s2 += 1;
        s3 += *(s32 *)(rec + 0x14);
        s4 += *(s32 *)(rec + 0x10);
    } while ((u32)s2 < (u32)count);
}
