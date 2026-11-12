#include "common.h"

s32 func_002C1078(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C10B0(s32 arg0, s32 arg1, s32 arg2);
s32 func_003045F0(s32 arg0);
s32 func_00305390(s32 arg0, s32 arg1, s32 arg2);

void func_002C0F30(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 vt;
    s32 r;
    s32 (*fn)(s32, s32);

    if (func_002C1078(arg0, (s32)arg1, (s32)arg2) != 0) {
        *arg1 = func_00305390(arg0, 1, 1);
        *arg2 = func_00305390(arg0, 0, 1);
        return;
    }
    if (func_002C10B0(arg0, 1, 1) != 0) {
        *arg1 = func_003045F0(arg0);
        vt = *(s32 *)arg0;
        fn = (s32 (*)(s32, s32))(*(s32 *)((u8 *)vt + 0x24));
        r = fn(arg0, 1);
        *arg2 = *arg1 - r;
        return;
    }
    *arg1 = 0;
    *arg2 = 0;
}
