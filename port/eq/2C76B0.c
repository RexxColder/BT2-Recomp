#include "common.h"

extern s32 D_0037A530[];

#define W(p, off) (*(s32 *)((p) + (off)))
#define LD(p, off) (*(s64 *)((p) + (off)))

s32 func_002C7830(s32 arg0, s32 arg1);
s32 memcmp(void *arg0, void *arg1, u32 arg2);

s64 func_002C76B0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4, u8 *arg5) {
    s64 v1;
    s64 ks;
    s32 s5;
    s32 s6;
    s32 t;
    s32 a0;

    s6 = D_0037A530[W(arg2, 0x10)];
    s5 = W(arg2, 0x14);

    v1 = LD(arg0, 0x150);
    if (v1 < 0) {
        t = func_002C7830(s5, s6);
        v1 = LD(arg3, 0) - (s64)t;
        if (v1 < 0) {
            v1 = 0;
        }
        LD(arg0, 0x150) = v1;
    }

    ks = LD(arg3, 0) - v1;
    if (ks < 0) {
        ks = 0;
    }

    if (memcmp(arg1 + 0x10, arg3, 4) != 0) {
        a0 = W(arg2, 0x18);
        LD(arg1, 0x10) = LD(arg3, 0);
        W(arg1, 0) = s5;
        LD(arg1, 0x18) = LD(arg3, 8);
        W(arg1, 4) = 0;
        W(arg1, 8) = (a0 == 3) ? 1 : 0;
        LD(arg5, 0) = LD(arg3, 0);
        return ks;
    }

    if (arg4 != 0) {
        a0 = W(arg1, 4) + W(arg1, 8) + 1;
        W(arg1, 0) = 0;
        W(arg1, 4) = a0;
        W(arg1, 8) = 0;
        a0 = W(arg1, 0);
    } else {
        a0 = W(arg1, 0);
    }

    a0 = s5 - a0;
    {
        s32 a2 = W(arg1, 4);
        s32 v = W(arg1, 8);
        if (!(a0 < v)) {
            v = a0;
        }
        W(arg1, 8) = v;
        t = func_002C7830(a2 + a0, s6);
    }
    ks = ks + (s64)t;
    if (ks < 0) {
        ks = 0;
    }
    return ks;
}
