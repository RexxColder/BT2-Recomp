#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

extern void *D_003879E8;

s32 rand(void);
void func_0026EAE0(void *arg0, s32 arg1, void *arg2, s32 arg3);
void func_0026EA88(void *arg0);

void func_00256C58(s32 arg0) {
    u8 *p;
    s32 s1, s0, a1, a3, off, t, v;
    s32 *arr;

    p = (u8 *)D_003879E8;
    if (p == NULL) {
        return;
    }
    W(p, 0x4C) = 0;
    W(p, 0x5C) = 0;
    W(p, 0x60) = 0;
    W(p, 0x50) = 0;
    W(p, 0x5C) = arg0;
    if (W(p, 0x5C) < 2) {
        W(p, 0x90) = W(p, 0x80);
        v = W(p, 0x84);
    } else {
        W(p, 0x90) = W(p, 0x88);
        v = W(p, 0x8C);
    }
    W(p, 0x94) = v;
    s1 = 0;
    s0 = 6;
    do {
        a1 = W(p, 0x90);
        t = 1 << (rand() % a1);
        if (!(s1 & t)) {
            s1 |= t;
            s0 -= 1;
        }
        a3 = 0;
    } while (s0 >= 0);

    s0 = 0;
    if (W(p, 0x90) > 0) {
        arr = (s32 *)(u32)W(p, 0x94);
        off = 0x60;
        t = 1 << a3;
        for (;;) {
            if (s1 & t) {
                W(p, off + 4) = arr[a3];
                s0 += 1;
                off += 4;
            }
            a3 += 1;
            if (!(a3 < W(p, 0x90))) {
                break;
            }
            t = 1 << a3;
            if (!(s0 < 7)) {
                break;
            }
        }
    }
    if (W(p, 0x5C) != 0) {
        W(p, 0x4C) = W(p, 0x4C) | 2;
        func_0026EAE0(p + 4, 0x1E, p, a3);
        func_0026EA88(p + 4);
    }
}
