#include "common.h"

extern s32 D_0037A078[] __attribute__((section(".data")));
extern u8 D_0037A2A0[] __attribute__((section(".data")));
void *func_002DCFE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void *func_002C2150(s32 arg0, s32 arg1, u8 *arg2, s32 arg3) {
    s32 pos = arg0;
    s32 remain = arg1;
    s32 a3 = arg3;
    u8 *rec;
    s32 n;
    u8 c4, c5, c6, c7, c8, c9, cB;
    s32 lo;

    if (remain <= 0) {
        return (void *)1;
    }
    for (;;) {
        rec = func_002DCFE8(pos, remain, 0x40, a3);
        if (rec == NULL) {
            return NULL;
        }
        n = ((s32)rec - pos) + 1;
        remain -= n;
        pos += n;
        c7 = rec[7];
        a3 = rec[0xA];
        c4 = rec[4];
        c5 = rec[5];
        c6 = rec[6];
        c8 = rec[8];
        c9 = rec[9];
        cB = rec[0xB];
        lo = c7 & 0xF;
        if ((c7 >> 4) != 0 && ((u32)((lo + 0xFF) & 0xFF) < 8U) && ((a3 >> 5) & 1)) {
            *(s32 *)(arg2 + 0x14) = (s32)((c4 * 0x10) | (c5 >> 4));
            *(s32 *)(arg2 + 0x18) = (s32)(((c5 & 0xF) << 8) | c6);
            if (*(s32 *)(arg2 + 0x1C) == 0) {
                *(s32 *)(arg2 + 0x1C) = (s32)(((c8 << 10) | (c9 * 4) | (a3 >> 6)) * 0x32);
            }
            *(u32 *)(arg2 + 8) = (u32)D_0037A2A0;
            *(s32 *)(arg2 + 0x20) = D_0037A078[lo];
            *(s32 *)(arg2 + 0x24) = (s32)((((a3 & 0x1F) << 5) | (cB >> 3)) << 11);
            return (void *)1;
        }
        if (remain <= 0) {
            return (void *)1;
        }
    }
}
