#include "common.h"

s32 func_002C0540(s32 arg0, s32 arg1, s32 arg2);
void func_002C03B8(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);

s32 func_002C0268(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *a0;
    u8 *s2;
    s32 s1;
    s32 s0;
    s32 s7;
    s32 t;
    s32 v;

    s7 = 0;
    a0 = arg0 + 0x1310 + (arg1 * 0x74);
    s2 = a0 + 0x10;
    s1 = *(s32 *)(s2 + 4);
    if (arg2 == 0) {
        return 0;
    }
    if (*(s32 *)(a0 + 4) == 0) {
        return 0;
    }
    if (s1 == 0) {
        return 0;
    }
    t = func_002C0540(s1, arg3, arg2);
    if (t < arg2) {
        s0 = arg2 - t;
        if (func_002C0540(s1, arg3, s0) < s0) {
            s7 = func_002C2FF0((s32)arg0, 0xFF00040B);
        }
    }
    if (arg3 != 1) {
        v = *(s32 *)(s2 + 0x20);
        if (v >= 0) {
            *(s32 *)(s2 + 0x20) = v + arg2;
        }
    } else {
        if (arg1 == arg3) {
            func_002C03B8((s32)s2);
        }
        v = *(s32 *)(s2 + 0x24);
        if (v >= 0) {
            *(s32 *)(s2 + 0x24) = v + arg2;
        }
    }
    *(s32 *)(arg0 + 0x44) = 1;
    return s7;
}
