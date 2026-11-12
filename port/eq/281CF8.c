#include "common.h"

u64 *Dma_BeginDirect(void);
void Dma_EndDirect(u64 *end);

/* low byte of a float colour channel: truncated integer, values >= 2^31 go through the subtract path */
static u32 vtxByte(f32 value) {
    s32 n;

    if (value >= 2147483648.0f) {
        n = (s32)(value - 2147483648.0f);
    } else {
        n = (s32)value;
    }
    return (u32)n & 0xFF;
}

void func_00281CF8(s32 arg0, s32 arg1) {
    f32 *vec;
    u8 *p;
    u8 *q;
    u64 *tail;
    u64 word0;
    u32 r;
    u32 g;
    u32 b;
    u32 a;
    s32 i;

    vec = (f32 *)arg1;
    p = (u8 *)Dma_BeginDirect();

    *(u64 *)(p + 0x00) = 0x1000000000000005ULL;
    *(u64 *)(p + 0x08) = 14;
    *(u64 *)(p + 0x10) = (u64)(s64)arg0;
    *(u64 *)(p + 0x18) = 66;
    *(u64 *)(p + 0x20) = 0x30000;
    *(u64 *)(p + 0x28) = 71;
    *(u64 *)(p + 0x30) = 0;
    *(u64 *)(p + 0x38) = 74;
    *(u64 *)(p + 0x40) = 70;
    *(u64 *)(p + 0x48) = 0;

    /* one RGBAQ word: R, G, B, A bytes and Q = 1.0f in the high half */
    r = vtxByte(vec[0]);
    b = vtxByte(vec[2]);
    g = vtxByte(vec[1]);
    a = vtxByte(vec[3]);
    word0 = 0x3F800000ULL << 32;
    word0 = word0 | r | ((u64)g << 8) | ((u64)b << 16) | ((u64)a << 24);
    *(u64 *)(p + 0x50) = word0;
    *(u64 *)(p + 0x58) = 1;

    tail = (u64 *)(p + 0x60);
    q = p + 0x70;

    for (i = 0; i < 16; i++) {
        *(u64 *)q = 0x72000000ULL | (u64)(0x7000 + 0x200 * i);
        *(u64 *)(q + 8) = 0x8E000000ULL | (u64)(0x7200 + 0x200 * i);
        q += 16;
    }

    tail[0] = 0x2400000000008010ULL;
    tail[1] = 85;

    Dma_EndDirect((u64 *)q);
}
