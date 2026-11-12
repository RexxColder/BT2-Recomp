#include "common.h"

s32 Dma_BeginDirect();
s32 Dma_EndDirect(s32 arg0);
extern u8 gGfx[] __attribute__((section(".data")));

#define QW(a, b) (p[0] = (u64)(a), p[1] = (u64)(b), p += 2)

s32 func_0027FD28(u8 *obj, s32 flag, s32 mode) {
    s32 width, height, yoff, rows, count;
    s32 colsm1;
    u64 *p;
    s32 n, i, d, a, b, k;
    s32 j;

    flag &= 0xFF;
    width = 0x200;
    height = 0x200;
    yoff = 0;
    rows = *(s32 *)(obj + 0x60C);
    count = *(s32 *)(obj + 0x610);
    if (flag != 0) {
        rows = rows / 2;
        height = 0x100;
        yoff = ((mode ^ 1) != 0) ? 0 : 0x100;
        width = 0x100;
    }
    p = (u64 *)Dma_BeginDirect();
    n = width / 0x20;
    QW(0x1000000000000008ULL, 0xE);
    QW(0x30000, 0x47);
    QW(0, 0x4A);
    QW(0x60, 0x14);
    QW((*(s32 *)(gGfx + 0x234) & 1) ? 0x264020000ULL : 0x264020E00ULL, 6);
    QW(0x80150, 0x4C);
    QW(0x1310000E0ULL, 0x4E);
    QW(((u64)(s64)(height - 1) << 16) | 0xDF000000000000ULL, 0x40);
    QW(((u64)(s64)yoff << 4) | 0x70000000000ULL | 0x800000 | 0xA, 8);
    QW(0x1000000000000002ULL, 0xE);
    QW(0x116, 0);
    QW(0x3F80000080808080ULL, 1);
    QW((u64)(s64)n | 0x4400000000000000ULL, 0x5353);
    if (n != 0) {
        d = height / n;
        a = (yoff + 0x20) * 16;
        b = yoff * 16;
        k = 0;
        i = d;
        for (j = 0; j < n; j++) {
            s32 v0, v1;
            v0 = (k >> 1) * 16 + 0x6FF8;
            v1 = (i >> 1) * 16 + 0x6FF8;
            k += d;
            i += d;
            QW(b, (u64)(s64)v0 | 0x71F80000);
            QW((u64)(s64)a | 0x1C000000, (u64)(s64)v1 | 0x7FF80000);
            a += 0x200;
            b += 0x200;
        }
    }
    QW(0x1000000000000006ULL, 0xE);
    QW(0x60, 0x14);
    QW(0x264022A00ULL, 6);
    QW((*(s32 *)(gGfx + 0x234) & 1) ? 0x80000 : 0x80070, 0x4C);
    QW((u64)(s64)yoff | 0x1FF0000 | 0x1BF000000000000ULL, 0x40);
    QW(((u64)(s64)height << 14) | 0x3800000000AULL, 8);
    colsm1 = count - 1;
    QW(0x54, 0x42);
    for (i = 0; i < colsm1; ) {
        s32 s1, s2, s3, s4, s5, s6, s7, ct;
        u8 *q0, *q1, *q2, *q3;
        s32 rm1;
        rm1 = rows - 1;
        QW(0x2400000000000001ULL, 0x10);
        QW(0x154, ((u64)0x3F80000000000000ULL | obj[0x61C] | ((u64)obj[0x61E] << 16) | ((u64)obj[0x61D] << 8) | ((u64)obj[0x61F] << 24)));
        q0 = obj + i * 12 + 0x48C;
        q1 = obj + i * 12 + 0x300;
        q2 = obj + i * 12 + 0x480;
        q3 = obj + i * 12 + 0x30C;
        QW((u64)(s64)rows | 0x4400000000000000ULL, 0x5353);
        if (rows > 0) {
            s32 t;
            s1 = 0x1C0 * (i + 1);
            s2 = 0xE0 * (i + 1);
            s4 = 0x1C0 * i;
            s3 = 0xE0 * i;
            s5 = s6 = s7 = 0;
            for (ct = rows; ct != 0; ct--) {
                s32 x0, y0, x1, y1, qa, qb, qc, qd, row;
                qa = s5 / rm1;
                qb = s3 / colsm1;
                qc = s6 / rm1;
                qd = s4 / colsm1;
                x0 = qa * 16 + (s8)*q1;
                y0 = qb * 16 + (s8)*q2;
                row = qc + yoff;
                if (x0 < 0) x0 = 0; else if (height * 16 < x0) x0 = height * 16;
                if (y0 < 0) y0 = 0; else if (0xE00 < y0) y0 = 0xE00;
                row += 0x700;
                QW((u64)(s64)(x0 >> 1) | ((u64)(s64)y0 << 16),
                   (u64)(s64)(row * 16 - 8) | ((u64)(s64)(qd * 16 + 0x71F8) << 16));
                qa = s7 / rm1;
                qb = s2 / colsm1;
                qc = s1 / colsm1;
                x1 = qa * 16 + (s8)*q3;
                y1 = qb * 16 + (s8)*q0;
                if (x1 < 0) x1 = 0; else if (height * 16 < x1) x1 = height * 16;
                if (y1 < 0) y1 = 0; else if (0xE00 < y1) y1 = 0xE00;
                QW((u64)(s64)(x1 >> 1) | ((u64)(s64)y1 << 16),
                   (u64)(s64)(row * 16 - 8) | ((u64)(s64)(qc * 16 + 0x71F8) << 16));
                q1++; q3++; q2++; q0++;
                s7 += height;
                s5 += height;
                s6 += width;
            }
        }
        i++;
    }
    QW(0x1000000000008005ULL, 0xE);
    QW(0x310000E0, 0x4E);
    QW(0x1BF000001FF0000ULL, 0x40);
    QW(0x70000, 0x47);
    QW(0, 8);
    p[0] = 0x44;
    p[1] = 0x42;
    return Dma_EndDirect((s32)(p + 2));
}
