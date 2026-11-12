#include "common.h"

void *Dma_BeginDirect(s32 arg0, s32 arg1);
s32 Dma_EndDirect(void *arg0);

#define F2I(x) ((x) >= 2147483648.0f ? (((u32)(s32)((x) - 2147483648.0f)) | 0x80000000u) : (u32)(s32)(x))

s32 func_002848C0(s32 arg0, s32 arg1) {
    f32 *s;
    u64 *p;
    u64 *q;
    u64 *t0;
    u64 *q2;
    u64 w0;
    u32 c0;
    u32 b1;
    u32 b2;
    u32 b3;
    s32 i;

    s = (f32 *)arg1;
    p = (u64 *)Dma_BeginDirect(arg0, arg1);
    p[0] = 0x1000000000000005ULL;
    p[1] = 0xE;
    p[2] = (u64)(u32)arg0;
    p[3] = 0x42;
    p[4] = 0x30000;
    p[5] = 0x47;
    p[6] = 0;
    p[7] = 0x4A;
    p[8] = 0x46;
    p[9] = 0;

    q = p + 10;
    c0 = F2I(s[0]) & 0xFF;
    b1 = F2I(s[1]) & 0xFF;
    b2 = F2I(s[2]) & 0xFF;
    b3 = F2I(s[3]) & 0xFF;
    w0 = (u64)c0 | 0x3F80000000000000ULL | ((u64)b1 << 8) | ((u64)b2 << 16) | ((u64)b3 << 24);
    q[0] = w0;
    q[1] = 1;

    t0 = q + 2;
    q2 = q + 4;
    for (i = 0; i < 16; i++) {
        q2[2 * i] = (u64)(0x7000 + 0x200 * i) | 0x72000000ULL;
        q2[2 * i + 1] = (u64)(0x7200 + 0x200 * i) | 0x8E000000ULL;
    }

    t0[0] = 0x2400000000008010ULL;
    t0[1] = 0x55;
    return Dma_EndDirect((void *)(q2 + 32));
}
