#include "common.h"

s32 func_00277E68(s32 arg0);

#define PK(lo, hi) ((u64)(s64)(s32)((lo) << 4) | ((u64)(s64)(s32)((hi) << 4) << 16))

/* 0x0026E468: builds a GS packet (GIF tag, register list, two-word vertices) at arg0 from the record at arg1. */
s32 func_0026E468(void *arg0, void *arg1, s64 arg2) {
    u64 *q;
    u8 *s1;
    u8 fr[0x20];
    s32 k;
    s32 w0;
    s32 w38;
    s32 w3c;
    s32 w40;
    s32 w44;
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spc;
    s32 fa;
    s32 fb;
    s32 fc;
    s32 fd;
    s32 xa;
    s32 xb;
    s32 xc;
    s32 xd;
    s32 ya;
    s32 yb;
    s32 yc;
    s32 yd;

    q = (u64 *)arg0;
    s1 = (u8 *)arg1;

    q[0] = 0xC400000000008001ULL;
    q[1] = 0x5353535306E1ULL;

    w38 = *(s32 *)(s1 + 0x38);
    w3c = *(s32 *)(s1 + 0x3C);
    w40 = *(s32 *)(s1 + 0x40);
    w44 = *(s32 *)(s1 + 0x44);
    q[2] = (u64)(s64)w38 | ((u64)(s64)w44 << 24) | ((u64)(s64)w40 << 16) | ((u64)(s64)w3c << 8);
    q[3] = 0;
    q[4] = (u64)arg2;
    q[5] = 0x154ULL;

    for (k = 0; k < 16; k++) {
        fr[k] = s1[0x24 + k];
    }
    w0 = *(s32 *)(s1 + 0);
    if ((w0 & 1) != 0) {
        *(s32 *)(fr + 0) = *(s32 *)(s1 + 0x2C);
        *(s32 *)(fr + 8) = *(s32 *)(s1 + 0x24);
    }
    if ((w0 & 2) != 0) {
        *(s32 *)(fr + 4) = *(s32 *)(s1 + 0x30);
        *(s32 *)(fr + 0xC) = *(s32 *)(s1 + 0x28);
    }
    sp0 = *(s32 *)(fr + 0);
    sp4 = *(s32 *)(fr + 4);
    sp8 = *(s32 *)(fr + 8);
    spc = *(s32 *)(fr + 0xC);

    q[6] = PK(sp0, sp4);

    fa = func_00277E68((s32)*(f32 *)(s1 + 0x8));
    ya = (s32)*(f32 *)(s1 + 0x4);
    xa = (fa << 4) + 0x7200;
    q[7] = (u64)(s64)(((ya << 4) + 0x7000)) | ((u64)(s64)xa << 16);
    q[8] = PK(sp8, sp4);

    fb = func_00277E68((s32)*(f32 *)(s1 + 0x10));
    yb = (s32)*(f32 *)(s1 + 0xC);
    xb = (fb << 4) + 0x7200;
    q[9] = (u64)(s64)(((yb << 4) + 0x7000)) | ((u64)(s64)xb << 16);
    q[10] = PK(sp0, spc);

    fc = func_00277E68((s32)*(f32 *)(s1 + 0x18));
    yc = (s32)*(f32 *)(s1 + 0x14);
    xc = (fc << 4) + 0x7200;
    q[11] = (u64)(s64)(((yc << 4) + 0x7000)) | ((u64)(s64)xc << 16);
    q[12] = PK(sp8, spc);

    fd = func_00277E68((s32)*(f32 *)(s1 + 0x20));
    yd = (s32)*(f32 *)(s1 + 0x1C);
    xd = (fd << 4) + 0x7200;
    q[13] = (u64)(s64)(((yd << 4) + 0x7000)) | ((u64)(s64)xd << 16);
    return (s32)((u8 *)arg0 + 0x70); /* v0 = s0 + 0x10: the end of the packet, for Dma_EndDirect */
}
