#include "common.h"

s32 *func_00202DA0(u8 *arg0, s32 arg1);
s32 *func_00202E60(u8 *arg0, s32 arg1);
s32 func_0023F4D8(u8 *arg0, s32 arg1, s32 arg2);

s32 func_00212690(u8 *arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s32 i;
    s32 s2;
    s32 *p;
    s32 r;
    s32 *q;

    i = 0;
    if (*(s32 *)(arg0 + 0x1184) <= 0) {
        return 0;
    }

    for (;;) {
        q = func_00202E60(arg0, i);
        if (*q > 0) {
            q = func_00202E60(arg0, i);
            if (*(u8 *)((u8 *)q + 0x2C) == 0) {
                s2 = 0;
                for (;;) {
                    p = func_00202DA0(arg0, i);
                    r = func_0023F4D8(arg0, arg1, s2);
                    s2 += 1;
                    if (*p == r) {
                        if (arg2 != NULL) {
                            *arg2 = *func_00202DA0(arg0, i);
                        }
                        if (arg3 != NULL) {
                            *arg3 = *(s32 *)((u8 *)func_00202DA0(arg0, i) + 0x4);
                        }
                        return 1;
                    }
                    if (s2 >= 6) {
                        break;
                    }
                }
            }
        }
        i += 1;
        if (i >= *(s32 *)(arg0 + 0x1184)) {
            return 0;
        }
    }
}
