#include "common.h"

void *Dma_BeginDirect(void);
void Dma_EndDirect(void *end);
void GfxPostQuad_Set(void *q, s32 baseX, s32 baseY, s32 u0, s32 v0, s32 u1, s32 v1, s32 dx, s32 dy, s32 w, s32 h,
                     s32 half);

void func_002814D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3) {
    s32 o[24];
    s64 *q;
    s64 *s1;
    s64 a2v;
    s64 s0v;
    s64 s4;
    s64 v0v;
    s32 cur;
    s32 cnt;

    q = (s64 *)Dma_BeginDirect();
    q[0] = 0x1000000000008008LL;
    q[1] = 0xE;
    a2v = 0xFFA8;
    s1 = q + 2;
    if (arg0 & 0xFF) {
        v0v = 0x70000;
    } else {
        v0v = 0x30000;
        a2v = 0;
    }
    q[2] = v0v;
    q[3] = 0x47;
    q[4] = arg3;
    q[5] = 0x42;
    q[6] = 0;
    q[7] = 0x3F;
    q[8] = 0x80000000LL;
    q[9] = 0x3B;
    q[10] = 0;
    q[11] = 0x14;
    q[12] = (s64)(u32)(arg1 | 0x25B20000) | (s64)((u64)arg2 << 37) | 0x2000000E40000000LL;
    q[13] = 6;
    q[14] = 0x156;
    q[15] = 0;
    q[16] = 0x3F80000080808080LL;
    q[17] = 1;
    s0v = (s64)((u64)a2v << 32);
    s1 = q + 20;

    cur = 0;
    s4 = 0;
    cnt = 0xF;
    do {
        cnt -= 1;
        GfxPostQuad_Set(o, 0x700, 0x720, (s16)cur, 0, (s16)(cur + 0x20), 0x1C0, (s32)s4, 0, 0x20, 0x1C0, 1);
        s4 += 0x20;
        cur += 0x20;
        s1[0] = (s64)o[8] | ((s64)o[9] << 16);
        s1[1] = (s64)o[4] | ((s64)o[5] << 16) | s0v;
        s1 += 2;
        s1[0] = (s64)o[10] | ((s64)o[11] << 16);
        s1[1] = (s64)o[6] | ((s64)o[7] << 16) | s0v;
        s1 += 2;
    } while (cnt >= 0);

    q[18] = 0x4400000000008010LL;
    q[19] = 0x5353;
    Dma_EndDirect(s1);
}
