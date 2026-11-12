#include "common.h"

s32 func_002CCB98(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002CCB08(u8 *arg0, s32 arg1) {
    s32 a1;
    s32 a2;
    s32 a3;
    s32 v;

    a1 = arg1;
    a2 = arg1;
    a3 = 0;
    if (a2 == 1) {
        v = *(s32 *)(arg0 + 0x54) + 1;
        *(s32 *)(arg0 + 0x54) = v;
        if (v == a2) {
            a3 = func_002CCB98((s32)arg0, a1, a2, a3);
        }
        return a3;
    }
    if (a2 == 0) {
        v = *(s32 *)(arg0 + 0x54) - 1;
        *(s32 *)(arg0 + 0x54) = v;
        if (v == 0) {
            a1 = 0;
            a3 = func_002CCB98((s32)arg0, a1, a2, a3);
        }
        return a3;
    }
    if (a2 == 2) {
        if (*(s32 *)(arg0 + 0x48) == 4) {
            a3 = func_002CCB98((s32)arg0, a1, a2, a3);
        }
        return a3;
    }
    return 0;
}
