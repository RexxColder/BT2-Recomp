#include "common.h"

s32 func_0020BDB0(s32 arg0);
s32 func_0020BE00(s32 arg0);
s32 func_0020BE80(s32 arg0);
s32 func_0020BD60(s32 arg0);
s32 func_0020C038(s32 arg0);
void func_00111A98(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_00111B50(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *s3;
    u8 *s2;
    s32 s0;
    s32 s1;
    s32 v;
    s32 cb;
    s32 r;

    s3 = arg0;
    s2 = arg1;
    s0 = arg2;
    s1 = arg3;

    if (func_0020BDB0(s0) != 0) {
        func_00111A98(s2, s0, s1, 0);
    }
    if (func_0020BE00(s0) != 0) {
        func_00111A98(s2, s0, s1, 1);
    }
    if (func_0020BE80(s0) != 0) {
        func_00111A98(s2, s0, s1, 2);
    }
    if (func_0020BD60(s0) != 0) {
        func_00111A98(s2, s0, s1, 3);
    }

    v = func_0020C038(s0);
    if ((u32)v < 5) {
        func_00111A98(s2, s0, s1, v + 4);
    }

    cb = *(s32 *)(s2 + 0xA4);
    if (cb == 0) {
        return 0;
    }
    {
        s32 (*cbFn)(u8 *, u8 *) = (s32 (*)(u8 *, u8 *))(u32)cb;
        r = cbFn(s3, s2 + 0x74);
    }
    if (r == 0) {
        return 1;
    }
    *(s32 *)(s2 + 0xA4) = 0;
    return 0;
}
