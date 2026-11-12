#include "common.h"
#include "sys/dma.h"

extern u8 D_00376F00[];

#define W(p, off) (*(s32 *)((p) + (off)))

void func_002865F0(u8 *arg0, s32 arg1, s32 arg2) {
    u8 sp[0x30];
    u8 *e;
    s32 s2;
    s32 s4;
    s32 i;
    s32 off;
    s32 k;

    s2 = arg2;
    s4 = arg1;
    for (k = 0; k < 0x30; k++) {
        sp[k] = D_00376F00[k];
    }

    if (W(arg0, 0) != 0) {
        i = 0;
        do {
            off = i * 0x40;
            i++;
            W(sp, 0x20) = 0;
            e = (u8 *)W(arg0, 0x10) + off;
            W(sp, 0x24) = (s32)((u32)s4 | (((u32)W(e, 0x18) & 0xFFFF) << 16));
            Dma_AddData(sp, 0x30);
            e = (u8 *)W(arg0, 0x10) + off;
            Dma_AddRef((void *)W(e, 0x38), W(e, 0x8));

            W(sp, 0x20) = 0;
            e = (u8 *)W(arg0, 0x10) + off;
            W(sp, 0x24) = (s32)((u32)s2 | (((u32)W(e, 0x1C) & 0xFFFF) << 16));
            Dma_AddData(sp, 0x30);
            e = (u8 *)W(arg0, 0x10) + off;
            Dma_AddRef((void *)W(e, 0x3C), W(e, 0xC));

            e = (u8 *)W(arg0, 0x10) + off;
            s2 += W(e, 0x14);
            s4 += W(e, 0x10);
        } while (i < W(arg0, 0));
    }
}
