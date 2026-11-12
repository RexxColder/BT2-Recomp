#include "common.h"

s32 func_0020ADA0(s32 a0);
s32 func_00101720(s32 a0);
s32 Ramp_Step(void *a0);
void func_00101700(s32 a0);

s32 func_0010A4D0(void *arg0) {
    u8 *s0;
    u8 st;
    s32 r;
    s32 (*fp)(void *);

    s0 = (u8 *)arg0;
    st = s0[8];
    if (st < 5) {
        switch (st) {
        case 0:
        case 1:
            r = func_0020ADA0(s0[9]);
            if (r != 0) {
                if (func_00101720(s0[9]) == 5) {
                    s0[8] = 2;
                } else if (Ramp_Step(s0 + 0x14) != 0) {
                    s0[8] = 2;
                }
            }
            break;
        case 2:
        case 3:
            if (Ramp_Step(s0 + 0x14) != 0) {
                s0[8] = 4;
            }
            break;
        case 4:
            return 6;
        }
    }
    r = *(s32 *)s0;
    if (r == 0) {
        return 5;
    }
    fp = (s32 (*)(void *))(void *)r;
    r = fp(*(void **)(s0 + 4));
    if (r == 0) {
        return 5;
    }
    func_00101700(s0[9]);
    return 6;
}
