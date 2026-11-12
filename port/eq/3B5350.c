#include "common.h"

extern u8 *D_0038B950 __attribute__((section(".data")));
extern u8 D_004217D8[] __attribute__((section(".data")));

extern void *memcpy(void *dst, const void *src, u32 n);
extern void *memset(void *dst, s32 c, u32 n);

/* 0x003B5350: builds count = arg1 / 16 packet blocks at D_0038B950 + running offset. Each block: a 0x80-byte work
 * area pkt (template D_004217D8[0..0x20) at pkt+0x00, GIF header words at pkt+0x20..0x7F, pkt+0x44 = block index * 16),
 * then the header pkt[0x20..0x80) (0x60 bytes), then arg0 + running src offset (chunk = arg2 << 6 bytes), then the
 * template pkt[0..0x20). Stride = chunk + 0x80. Returns chunk + 0x80. */
s32 func_003B5350(u8 *arg0, s32 arg1, s32 arg2) {
    u8 pkt[0x80];
    s32 s1;
    s32 s5;
    s32 s2;
    s32 s6;
    s32 i;
    s32 n;
    u32 v0;
    u32 v1;

    s1 = (s32)((u32)arg2 << 6);
    s5 = s1 + 0x80;
    v1 = ((u32)s5 >> 4) + 0x4FFFFFFF;
    v0 = ((u32)s1 >> 4) | 0x8000;

    memcpy(pkt, D_004217D8, 0x20);
    memset(pkt + 0x20, 0, 0x60);
    *(u32 *)(pkt + 0x2C) = v1;
    *(u32 *)(pkt + 0x30) = 0x8003;
    *(u32 *)(pkt + 0x34) = 0x10000000;
    *(u32 *)(pkt + 0x38) = 0xE;
    *(u32 *)(pkt + 0x48) = 0x51;
    *(u32 *)(pkt + 0x50) = 0x10;
    *(s32 *)(pkt + 0x54) = arg2;
    *(u32 *)(pkt + 0x58) = 0x52;
    *(u32 *)(pkt + 0x68) = 0x53;
    *(u32 *)(pkt + 0x70) = v0;
    *(u32 *)(pkt + 0x74) = 0x8000000;

    s2 = 0;
    s6 = 0;
    n = arg1 / 16;
    for (i = 0; i < n; i++) {
        *(u32 *)(pkt + 0x40) = 0;
        *(s32 *)(pkt + 0x44) = i << 4;

        memcpy(D_0038B950 + s2, pkt + 0x20, 0x60);
        memcpy(D_0038B950 + s2 + 0x60, arg0 + s6, s1);
        s6 += s1;
        memcpy(D_0038B950 + s2 + s1 + 0x60, pkt, 0x20);
        s2 += s5;
    }
    return s5;
}
