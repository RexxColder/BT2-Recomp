#include "common.h"

s32  func_00123478(u8 *arg0) {
    u8 *t = arg0 + 0x160;
    u8 v = 0xFF;
    s32 n = *(s32 *)(t + 0x2C);

    if (n > 0) {
        s32 idx = *(s32 *)(t + 0x28);
        s32 nx = idx + 1;

        v = arg0[idx + 0x99C];
        *(s32 *)(t + 0x2C) = n - 1;
        *(s32 *)(t + 0x28) = nx;
        if (nx >= 0x100) {
            *(s32 *)(t + 0x28) = 0;
        }
    }
    return (u8)(v);
}
