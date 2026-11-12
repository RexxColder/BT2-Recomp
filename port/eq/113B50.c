#include "common.h"

void func_00113B50(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *t0;
    s32 t1;
    s32 t2;
    s32 v0;

    if (*arg0 & 2) {
        return;
    }
    t1 = arg3;
    t2 = arg2;
    t0 = (u8 *)arg0;
    v0 = *(s32 *)t0;
    for (;;) {
        if (v0 & 1) {
            *(u16 *)(t0 + 4) = (u16)(*(u16 *)(t0 + 4) + t2);
            *(u16 *)(t0 + 8) = (u16)(*(u16 *)(t0 + 8) + t2);
            *(u16 *)(t0 + 6) = (u16)(*(u16 *)(t0 + 6) + t1);
            *(u16 *)(t0 + 0xA) = (u16)(*(u16 *)(t0 + 0xA) + t1);
            if ((arg1 & 0xFF) == 1) {
                t2 += arg2;
                t1 += arg3;
            }
        }
        t0 += 0x60;
        if (*(s32 *)t0 & 2) {
            break;
        }
        v0 = *(s32 *)t0;
    }
}
