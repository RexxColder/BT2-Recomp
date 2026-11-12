#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A0(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_001F9138(s32 arg0);

s32 BtlObj_TickTimers(s32 arg0) {
    u8 *self;
    s32 j;
    s32 k;
    s32 *timer;
    u8 *flag;
    s32 s1;
    s32 r;

    self = (u8 *)arg0;
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 2; k++) {
            timer = (s32 *)(self + 0xB04 + 20 * j + 4 * k);
            flag = self + 0xAFA + 20 * j + k;
            *timer = *timer - 1;
            if (*timer <= 0) {
                *timer = 0;
                *flag = 0;
            }
        }
    }

    s1 = func_001FA3A8(BtlObjXf_Update(arg0));
    r = func_001FA3A8(func_001FA3A0(arg0));
    if ((r & 0x50) == 0x40) {
        if ((s1 & 0x50) != 0x40) {
            return func_001F9138(arg0);
        }
        return s1 & 0x50;
    }
    return r;
}
