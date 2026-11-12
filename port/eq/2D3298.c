#include "common.h"

#define LD(p, o) (*(s64 *)((u8 *)(p) + (o)))
#define SD(p, o, v) (*(s64 *)((u8 *)(p) + (o)) = (s64)(v))
#define LW(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define SW(p, o, v) (*(s32 *)((u8 *)(p) + (o)) = (s32)(v))

extern void *D_00346E8C __attribute__((section(".data")));

s64 __divdi3(s64 arg0, s64 arg1);
s64 __muldi3(s64 arg0, s64 arg1);
void func_002D3178(void *arg0, s64 arg1);
s64 func_002D3700(void *arg0, s64 arg1);
void func_002D3760(void *arg0, s64 arg1);
void func_002D3988(void *arg0, s32 arg1);

void func_002D3298(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 s2;
    s64 s1;
    s64 s4;
    s64 a1;
    s64 a1o;
    s64 a2v;
    s64 d;
    s64 q;
    s64 qs;
    s64 r;
    s64 absr;
    s64 qa;
    s64 t;
    s64 mid;
    s64 pv;
    s64 v;
    s64 a3v;
    s32 cmp;
    s32 v0w;
    s32 v1w;

    if (LD(arg2, 8) == 1 || LW(arg0, 0) == 0) {
        SD(arg3, 0, LD(arg1, 0));
        SD(arg3, 8, LD(arg1, 8));
        return;
    }

    a1 = LD(arg1, 0);
    v = LD(arg0, 0x188);
    if (a1 < v) {
        a1 = v;
    }
    SD(arg1, 0, a1);

    if (LW(arg0, 4) == 1) {
        SW(arg0, 8, 0);
        s2 = 0;
    } else {
        s2 = LW(arg0, 8);
        if (s2 == 0) {
            a2v = LD(arg0, 0x188);
            if (a2v >= a1) {
                if (LW(arg0, 0xC) == 0) {
                    SW(arg0, 8, 1);
                    s2 = 1;
                }
            } else {
                SW(arg0, 8, 1);
                if (LD(arg0, 0x178) == -1) {
                    q = __divdi3(__muldi3(LD(arg1, 8), LD(arg0, 0x158)), LD(arg0, 0x160));
                } else {
                    q = __divdi3(__muldi3(LD(arg1, 8), LD(arg0, 0x168)), LD(arg0, 0x170));
                }
                SD(arg0, 0x178, LD(arg2, 0));
                SD(arg0, 0x180, LD(arg1, 0) + q);
                func_002D3178(arg0, q);
                s2 = LW(arg0, 8);
            }
        }
    }

    /* common tail (asm 0x2D33EC) */
    v = LD(arg1, 0);
    a2v = LD(arg0, 0x188);
    if (v < a2v) {
        v = a2v;
    }
    SD(arg0, 0x188, v);
    s1 = LD(arg0, 0x178);
    if (s1 != -1) {
        s4 = LD(arg0, 0x180) + __divdi3(__muldi3(LD(arg1, 8), LD(arg2, 0) - s1), LD(arg2, 8));
    } else {
        s4 = 0;
    }

    if (s2 == 0) {
        v = LD(arg0, 0x188);
        if (v < s4) {
            if (LW(arg0, 0xC) == 0) {
                SD(arg0, 0x178, LD(arg2, 0));
                SD(arg0, 0x180, LD(arg0, 0x128));
            } else {
                SD(arg0, 0x180, v);
                SD(arg0, 0x178, LD(arg2, 0));
            }
            SW(arg0, 0x190, LW(arg0, 0x190) + 1);
            s1 = LD(arg0, 0x178);
        }
        goto l35e8;
    }

    if (LW(arg0, 0xC) != 1) {
        goto l35e8;
    }

    q = __divdi3(__muldi3(LD(arg1, 8), LD(arg0, 0x148)), LD(arg0, 0x150));
    a1o = LD(arg1, 0);
    d = a1o - s4;
    if (d < 0) {
        a1 = d;
        if (q < s4 - a1o) {
            goto b39;
        }
        goto b40;
    }
    if (q < d) {
        a1 = a1o;
        goto b39;
    }
    a1 = d;
    goto b40;

b39:
    SD(arg0, 0x178, LD(arg2, 0));
    SD(arg0, 0x180, LD(arg1, 0));
    func_002D3178(arg0, a1);
    s2 = LW(arg0, 8);
    SW(arg0, 0x1A0, LW(arg0, 0x1A0) + 1);
    s1 = LD(arg0, 0x178);
    goto l35e8;

b40:
    r = func_002D3700(arg0, (s64)(s32)a1);
    qs = __divdi3(__muldi3(LD(arg1, 8), LD(arg0, 0x138)), LD(arg0, 0x140));
    absr = (r < 0) ? -r : r;
    if (qs < absr) {
        if (qs < r) {
            qa = __divdi3(r * 2, qs) - 1;
            SW(arg0, 0x194, LW(arg0, 0x194) + (s32)qa);
        } else {
            qa = __divdi3(r * 2, qs) + 1;
            SW(arg0, 0x198, LW(arg0, 0x198) - (s32)qa);
        }
        t = __muldi3(qa, qs);
        mid = ((s64)((u64)t >> 63) + t) >> 1;
        SD(arg0, 0x178, LD(arg2, 0));
        SD(arg0, 0x180, s4 + mid);
        func_002D3760(arg0, (s64)(s32)mid);
    }
    s2 = LW(arg0, 8);
    s1 = LD(arg0, 0x178);

l35e8:
    if (s1 == -1) {
        pv = 0;
    } else {
        pv = LD(arg0, 0x180) + __divdi3(__muldi3(LD(arg1, 8), LD(arg2, 0) - s1), LD(arg2, 8));
    }

    SD(arg3, 0, pv);
    SD(arg3, 8, LD(arg1, 8));
    if (pv < LD(arg0, 0x128)) {
        SD(arg3, 0, LD(arg0, 0x128));
        SD(arg3, 8, LD(arg0, 0x130));
    }

    SD(arg0, 0x108, LD(arg1, 0));
    SD(arg0, 0x110, LD(arg1, 8));
    SD(arg0, 0x118, LD(arg2, 0));
    SD(arg0, 0x120, LD(arg2, 8));
    SD(arg0, 0x128, LD(arg3, 0));
    SD(arg0, 0x130, LD(arg3, 8));

    a3v = (s32)(LD(arg1, 0) - LD(arg3, 0));

    if (s2 != 0) {
        v0w = LW(arg0, 0x1B4);
        v1w = LW(arg0, 0x1B8);
        cmp = v1w < a3v;
        SW(arg0, 0x1B4, (a3v >= v0w) ? a3v : v0w);
        SW(arg0, 0x1B8, cmp ? v1w : a3v);
    } else {
        v0w = LW(arg0, 0x1AC);
        v1w = LW(arg0, 0x1B0);
        cmp = v1w < a3v;
        SW(arg0, 0x1AC, (a3v >= v0w) ? a3v : v0w);
        SW(arg0, 0x1B0, cmp ? v1w : a3v);
    }

    D_00346E8C = arg0;
    func_002D3988(arg0, cmp);
}
