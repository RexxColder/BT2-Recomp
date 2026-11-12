#include "common.h"

s32 func_0026CCF8(u8 *arg0, u32 arg1, s32 arg2) {
    u8 sp0;
    u8 sp1;
    s32 a3 = 0;
    u32 t0 = 0;
    s32 v0 = 0;
    s32 len;
    u8 v;
    u8 *p;

    if (arg1 != 0) {
        do {
            do {
                v = arg0[a3];
                a3 += 1;
            } while (v != 0);
            p = arg0 + a3;
            sp0 = p[0];
            sp1 = p[1];
            a3 += 2;
            len = (s32)sp0 | ((s32)sp1 << 8);
            v0 = 0;
            a3 += len;
            if (len == 0) {
                return v0;
            }
            t0 += 1;
        } while (t0 < arg1);
    }
    v0 = (s32)(arg0 + a3);
    if ((arg2 & 0xFF) == 0) {
        do {
            v = arg0[a3];
            a3 += 1;
        } while (v != 0);
        v0 = (s32)(arg0 + a3);
    }
    return v0;
}
