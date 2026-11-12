#include "common.h"

extern u8 D_00376FC0[] __attribute__((section(".data")));

void Dma_AddData(u8 *arg0, s32 arg1);
void Dma_AddRef(s32 arg0, s32 arg1);

void func_00286B60(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 buf[48];
    s32 s1;
    s32 s2;
    s32 s5;
    s32 s6;
    s32 s4;
    s32 s3;
    u8 *rec;
    s32 hi;

    s5 = arg1;
    s6 = arg2;
    s4 = arg3;
    s3 = arg4;
    memcpy(buf, D_00376FC0, 48);
    s1 = 0;
    s2 = 0;
    if (*(s32 *)arg0 == 0) {
        return;
    }
    do {
        if (s2 < s5) {
            s2++;
        } else if (!(s2 < s5 + s6)) {
            s2++;
        } else {
            if (s4 >= 0) {
                rec = *(u8 **)(arg0 + 0x10) + s1;
                hi = (*(s32 *)(rec + 0x20) + s4) | (s32)((*(u32 *)(rec + 0x18) & 0xFFFF) << 16);
                *(s32 *)(buf + 0x20) = 0;
                *(s32 *)(buf + 0x24) = hi;
                Dma_AddData(buf, 0x30);
                rec = *(u8 **)(arg0 + 0x10) + s1;
                Dma_AddRef(*(s32 *)(rec + 0x38), *(s32 *)(rec + 0x8));
            }
            if (s3 >= 0) {
                rec = *(u8 **)(arg0 + 0x10) + s1;
                hi = (*(s32 *)(rec + 0x24) + s3) | (s32)((*(u32 *)(rec + 0x1C) & 0xFFFF) << 16);
                *(s32 *)(buf + 0x20) = 0;
                *(s32 *)(buf + 0x24) = hi;
                Dma_AddData(buf, 0x30);
                rec = *(u8 **)(arg0 + 0x10) + s1;
                Dma_AddRef(*(s32 *)(rec + 0x3C), *(s32 *)(rec + 0xC));
            }
            s2++;
        }
        s1 += 0x40;
    } while ((u32)s2 < (u32)*(s32 *)arg0);
}
