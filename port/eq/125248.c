#include "common.h"

s32 func_00126040(s32 arg0);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);

void func_00125248(u8 *arg0) {
    u8 *s0;
    u8 *p;
    s32 i;
    s32 a;
    s32 b;
    s32 sum;
    s32 r;

    s0 = arg0 + 0x10A0;
    r = func_00126040((s32)arg0);
    r = func_00210DD8(r);
    p = (u8 *)func_00211288(r);

    for (i = 0; i < 10; i++) {
        a = *(s32 *)(p + 0x14AC + 4 * i);
        b = *(s32 *)(p + 0x14D4 + 4 * i);
        sum = a + b;
        if (sum == 0) {
            *(s32 *)(s0 + 0xBC + 4 * i) = 0;
        } else {
            *(f32 *)(s0 + 0xBC + 4 * i) = (f32)b / (f32)sum;
        }
    }
}
