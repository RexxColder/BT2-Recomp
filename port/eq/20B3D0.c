#include "common.h"

s32 func_00210DD8(s32 arg0);
s32 func_00211288(u32 arg0);
void *func_002B1DD0(s32 arg0);
extern s32 D_00387930;
extern u8 *D_00387E18;

s32 func_0020B3D0(u32 arg0) {
    s32 s0;

    if (D_00387930 != 0) {
        if (arg0 < 2U) {
            return func_00210DD8(func_00211288(arg0));
        }
    }
    if (D_00387E18 == NULL) {
        return -1;
    }
    if (arg0 >= 3U) {
        return -1;
    }
    if (*(s32 *)(D_00387E18 + 4) <= 0) {
        return -1;
    }
    for (s0 = 0; s0 < *(s32 *)(D_00387E18 + 4); s0++) {
        if (s0 == (s32)arg0) {
            continue;
        }
        if (*(s32 *)((u8 *)func_002B1DD0(s0) + 0x10) == 3) {
            return s0;
        }
    }
    return -1;
}
