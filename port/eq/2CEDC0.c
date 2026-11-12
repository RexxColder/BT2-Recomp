#include "common.h"

f32 __floatdisf(s64 arg0);
s64 __muldi3(s64 arg0, s64 arg1);
s64 func_002D2750(void);
s64 func_002D2800(void);

void func_002CEDC0(u8 *arg0) {
    s64 v;
    s64 s1;
    s32 a2;
    f32 f20;

    *(s64 *)(arg0 + 0x3788) = func_002D2750();
    v = func_002D2800();
    a2 = *(s32 *)(arg0 + 0x968);
    *(s32 *)(arg0 + 0x3798) = a2;
    s1 = *(s64 *)(arg0 + 0x3788) - *(s64 *)(arg0 + 0x3780);
    *(s64 *)(arg0 + 0x3790) = v;
    if (s1 != 0) {
        f20 = __floatdisf(__muldi3((s64)a2, v));
        *(f32 *)(arg0 + 0x379C) = f20 / __floatdisf(s1);
    }
}
