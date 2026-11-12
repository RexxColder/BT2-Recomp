#include "common.h"

extern s32 D_00355380 __attribute__((section(".data")));
extern s32 D_00355384 __attribute__((section(".data")));
extern s32 D_0035538C __attribute__((section(".data")));
extern s32 D_003553BC __attribute__((section(".data")));
extern s32 D_0037DEB8 __attribute__((section(".data")));

void func_00306F58();
s32 func_002FC550();
s32 func_00306FD0();
s32 sceCdGetError(void);
s32 func_00331710(s32 arg0, s32 arg1);

/* 0x002FBB88: when the global D_00355384 is set and byte +2 of arg0 is 2, runs a CD error
 * query (two command paths chosen by D_00355380 == 1), stores the error in D_003553BC, and
 * for an error code other than 0 and 0x20 records it at arg0+0x34, reports it through
 * func_00331710 and returns 1. Otherwise returns 0. */
s32 func_002FBB88(u8 *arg0) {
    s32 s0 = 0;

    if (D_00355384 != 0 && *(s8 *)(arg0 + 2) == 2) {
        D_0035538C = 1;
        if (D_00355380 == 1) {
            func_00306F58((s32)&D_0035538C, 1);
            func_002FC550(0x1400);
            s0 = sceCdGetError();
            func_002FC550(0x1401);
            func_00306FD0();
        } else {
            func_002FC550(0x1500, 1);
            s0 = sceCdGetError();
            func_002FC550(0x1501);
        }
        D_003553BC = s0;
        D_0035538C = 0;
        if ((u32)(s0 + 1) >= 2) {
            if (s0 != 0x20) {
                *(s32 *)(arg0 + 0x34) = s0;
                func_00331710((s32)&D_0037DEB8, s0);
                return 1;
            }
        }
        return 0;
    }
    return 0;
}
