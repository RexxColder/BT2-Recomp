#include "common.h"

extern u8 D_00344F34[] __attribute__((section(".data")));

void func_002AA100(s32 arg0, s32 arg1, s32 arg2) {
    u32 v1;
    u32 a2;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 s_v1;
    s32 v0;
    s32 a3;
    s32 nxt;

    v1 = (u32)arg2 - 0x21u;
    if (v1 < 0x26Du) {
        a2 = v1;
        t2 = 0;
        t1 = 0;
        t0 = 0;
        for (;;) {
            s_v1 = *(s32 *)(D_00344F34 + t0);
            v0 = (s32)a2 - s_v1 * 3;
            if (v0 >= 0) {
                t1 += 1;
                a2 = (u32)v0;
                t0 = t1 * 16;
                if (t1 < 0x19) {
                    continue;
                }
                break;
            }
            t2 = 0;
            if (s_v1 > 0) {
                a3 = (s32)a2 - 3;
                if (a3 >= 0) {
                    for (;;) {
                        t2 += 1;
                        nxt = a3 - 3;
                        if (t2 < s_v1) {
                            a3 = nxt;
                            if (nxt >= 0) {
                                continue;
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
        *(s32 *)arg0 = t1;
        *(s32 *)arg1 = t2;
        return;
    }
    if ((u32)(arg2 - 0x2FF) < 0x19u) {
        *(s32 *)arg0 = arg2 - 0x2FF;
        *(s32 *)arg1 = 0;
    }
}
