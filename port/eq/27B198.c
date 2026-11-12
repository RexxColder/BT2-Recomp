#include "common.h"

extern s32 D_003B0A84 __attribute__((section(".data")));

void *Dma_BeginDirect(void);
void Dma_EndDirect(void *end, s64 arg1, s64 arg2, s64 arg3);

void func_0027B198(s32 arg0, s32 arg1) {
    s64 s0;
    s64 s1;
    s64 s2;
    s64 t4;
    s64 t0;
    s64 t1;
    s64 t3;
    s64 t5;
    s64 t6;
    s64 t7;
    s64 a0;
    s64 a1;
    s64 a2;
    s64 a3;
    s64 a1v;
    s64 a2v;
    s64 a3v;
    s64 a0v;
    s64 v0v;
    s64 v1v;
    s64 count;
    s64 *q;
    s32 flag;
    s32 g;

    flag = arg0 & 0xFF;
    g = D_003B0A84;

    if (flag == 0) {
        s1 = 0x200;
        s2 = 0x100;
        s0 = ((g & 1) != 0) ? 0 : 0xE00;
    } else if (arg1 != 0) {
        s1 = 0x100;
        s2 = 0x80;
        s0 = ((g & 1) != 0) ? 0x80 : 0xE80;
    } else {
        s1 = 0x100;
        s2 = 0x80;
        s0 = ((g & 1) != 0) ? 0 : 0xE00;
    }

    q = (s64 *)Dma_BeginDirect();
    q[0] = 0x1000000000000008LL;
    q[1] = 0xE;
    q[2] = 0x30000;
    q[3] = 0x47;
    q[4] = 0;
    q[5] = 0x4A;
    q[6] = 0x60;
    q[7] = 0x14;
    v1v = (s64)0x24020000 | s0;
    v0v = (s64)0x9000 << 18;
    q[8] = v1v | v0v;
    q[9] = 6;
    q[10] = 0x40150;
    q[11] = 0x4C;
    q[12] = ((((s64)1 << 16) | 0x3100) << 16) | 0xE0;
    q[13] = 0x4E;
    a2v = (s64)0xDF00 << 40;
    a3v = (s64)0xDF80 << 27;
    a0v = ((s64)(s2 - 1) << 16) | a2v;
    v0v = (((s64)(s1 - 1)) << 14) | a3v;
    v0v = v0v | 0xA;
    q[14] = a0v;
    q[15] = 0x40;
    q[16] = v0v;
    q[17] = 8;
    q[18] = 0x1000000000000002LL;
    q[19] = 0xE;
    q[20] = 0x116;
    q[21] = 0;
    q[22] = 0x3F80000080808080LL;
    q[23] = 1;
    a1v = (s64)0x8800 << 47;
    t4 = s1 / 32;
    q[24] = (t4 | 0x8000) | a1v;
    q[25] = 0x5353;
    q += 26;

    if (t4 == 0) {
        Dma_EndDirect(q, a1v, a2v, a3v);
        return;
    }

    count = s2 / t4;
    a2 = count << 4;
    s0 = 0x72000000;
    t7 = 0x1C000000;
    t6 = 0x80000000;
    a1 = a2 + 0x7000;
    t1 = 0x200;
    t0 = 0x7000;
    a3 = 0;
    t3 = 0x200;
    t5 = 0;
    do {
        v0v = t0 | s0;
        t0 += a2;
        t5 += 1;
        q[0] = a3;
        q[1] = v0v;
        q += 2;
        v1v = t1 | t7;
        t1 += t3;
        v0v = a1 | t6;
        a1 += a2;
        a0 = (t5 < t4);
        q[0] = v1v;
        q[1] = v0v;
        q += 2;
        a3 += t3;
    } while (a0 != 0);

    Dma_EndDirect(q, a1, a2, a3);
}
