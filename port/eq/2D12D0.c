#include "common.h"

s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00346E7C __attribute__((section(".data")));
extern s32 D_00346E80 __attribute__((section(".data")));

s32 func_002D12D0(s32 arg0, s32 arg1, s32 *arg2) {
    s32 v = *(s32 *)(arg0 + 0x118);
    s32 s0;
    s32 a2v;
    s32 ret;

    *arg2 = v;
    if (v != 0) {
        a2v = *(s32 *)(arg0 + 0x140);
        s0 = *(s32 *)(arg0 + 0x13C);
    } else {
        s0 = *(s32 *)(arg0 + 0x110);
        if (s0 < 0) {
            return -1;
        }
        a2v = *(s32 *)(arg0 + 0x114);
    }
    ret = func_002E0A98(s0, arg1, a2v);
    D_00346E7C = s0;
    D_00346E80 = ret;
    return ret;
}
