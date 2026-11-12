#include "common.h"

u8 *BtlKiBlast_Get(s32 arg0);
s32 func_001F9908(s32 arg0);

s32 func_00240238(s32 arg0) {
    u8 *p = BtlKiBlast_Get(arg0);
    s32 s1 = *(s8 *)(p + 0x32);
    s32 r = func_001F9908(arg0);
    s32 v = (s32)((u32)*(s32 *)(p + 8) * (u32)r);

    v = v / 100;
    if (s1 > 0) {
        v = v / s1;
    }
    return v;
}
