#include "common.h"

s32 *func_0012B9B0(s32 *a0, s32 a1, s64 a2);
s32 func_00129720(s32 *a0, s32 *a1, s32 *a2, s32 a3);
void func_00129A50(void *a0, void *a1, s32 *a2, s32 a3);
void func_0012DA70(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2, void *t3,
                   void *st0, s32 st1, s32 st2, s32 st3, s32 st4, s64 st5);

void func_001B5150(s32 *arg0, s32 arg1, s64 arg2) {
    s32 frame[0x1B0 / 4];
    u8 *sp = (u8 *)frame;
    s32 *s0;
    u8 *sc;
    u8 *a;
    u8 *b;
    u8 *p;
    u8 *t4;
    u8 *t0v;
    u8 *t1v;
    s32 s2;
    s32 s3 = 0xFFFFFF;
    s32 s4;
    s32 s5 = 3;
    s32 v1;
    s32 off;
    s32 q;
    s32 sum;

    s0 = func_0012B9B0(arg0, arg1, arg2);
    s2 = 4;
    s4 = 3;
    do {
        s4 = func_00129720(arg0, arg0, s0, s4);
        s2 -= 1;
        s0 += 4;
    } while (s2 >= 0);
    if (s4 == 0) {
        return;
    }
    p = sp + 0x30;
    a = sp + 0xC0;
    func_00129A50(p, a, arg0, s4);
    s2 = 2;
    if (2 < s4) {
        u8 *fp = (u8 *)arg0 + 0x20;
        sc = (u8 *)arg0 + 0x60;
        b = sp + 0x48;
        v1 = *(s32 *)b;
        for (;;) {
            off = s2 << 4;
            t4 = a + off;
            sum = *(s32 *)(sp + 0x38) + v1 + *(s32 *)(b + 0x10);
            *(s32 *)(sp + 0x38) = s3;
            q = (sum / s5) >> 8;
            *(s32 *)b = s3;
            *(s32 *)(b + 0x10) = s3;
            b += 0x10;
            t0v = sc - 0x10;
            t1v = sc + 0x20;
            sc += 0x30;
            s2 += 1;
            func_0012DA70(p, p + off - 0x10, p + off, fp, t0v, t1v, a, t4 - 0x10,
                          t4, 0, 0, arg1, q, arg2);
            if (!(s2 < s4)) {
                break;
            }
            v1 = *(s32 *)b;
        }
    }
}
