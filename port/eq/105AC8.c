#include "common.h"

s32 func_00105AB8(void);
s32 rand(void);

void func_00105AC8(u8 *arg0) {
    f32 w30;
    f32 w34;
    s32 v;
    s64 mask;

    w30 = *(f32 *)(arg0 + 0x30);
    w34 = *(f32 *)(arg0 + 0x34);
    mask = (s64)0x8000 << 19;
    if (w30 == w34) {
        v = 1;
        if (!(*(s64 *)(arg0 + 8) & mask)) {
            v = 2;
            if (!(*(s64 *)(arg0 + 0x10) & mask)) {
                v = 4;
                if (func_00105AB8() == 0) {
                    v = (rand() & 1) ? 1 : 2;
                }
            }
        }
    } else {
        v = (w34 < w30) ? 1 : 2;
    }
    *(s32 *)arg0 = v;
}
