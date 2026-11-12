#include "common.h"

extern u8 D_004217F8[] __attribute__((section(".data")));
extern u8 *D_0038B950 __attribute__((section(".data")));

void func_00271370(void);
void Dma_AddData(void *src, s32 size);
void Dma_AddRef(void *addr, s32 size);

/* 0x003B5620: copies the 0x30-byte template D_004217F8 to a local buffer (ldl/ldr/sdl/sdr). If arg0 > 0: func_00271370();
 * if arg3 >= 0: for n = 0 .. ((arg1 < 0 ? arg1 + 0xF : arg1) >> 4) - 1: buf+0x20 = 0, buf+0x24 = arg3 | (((arg1 +
 * (arg1 < 0 ? 0x3F : 0)) >> 6) & 0xFFFF) << 16, Dma_AddData(buf, 0x30), Dma_AddRef(*D_0038B950 + total, arg0),
 * total += arg0. */
void func_003B5620(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 buf[0x30];
    s32 total = 0;
    s32 i;
    s32 n;
    s32 q;

    memcpy(buf, D_004217F8, 0x30);

    if (arg0 <= 0) {
        return;
    }
    func_00271370();
    if (arg3 < 0) {
        return;
    }

    n = (arg1 < 0 ? arg1 + 0xF : arg1) >> 4;
    q = (arg1 < 0 ? arg1 + 0x3F : arg1) >> 6;
    for (i = 0; i < n; i++) {
        *(s32 *)(buf + 0x20) = 0;
        *(s32 *)(buf + 0x24) = (u32)arg3 | (((u32)q & 0xFFFF) << 16);
        Dma_AddData(buf, 0x30);
        Dma_AddRef(D_0038B950 + total, arg0);
        total += arg0;
    }
}
