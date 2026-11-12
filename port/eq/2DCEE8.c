#include "common.h"

s32 func_002DCE50(s8 *arg0);

s8 *func_002DCEE8(u32 arg0, s32 arg1, s32 arg2) {
    s32 state;
    u32 s1;
    s8 *p;
    s8 ch;
    s32 cont;
    s32 r;

    state = 0;
    s1 = arg0 - arg1;
    if (!(s1 < arg0)) {
        return NULL;
    }
    p = (s8 *)arg0 - 1;
    for (;;) {
        ch = *p;
        if (state == 0) {
            state = 1;
        } else if (state == 1) {
            if (ch == 1) {
                state = 2;
            }
        } else if (state == 2) {
            if (ch == 0) {
                state = 3;
            } else if (ch != 1) {
                state = 1;
            }
        } else {
            if (ch != 0) {
                state = (((ch ^ 1) == 0) ? 2 : 1);
            } else {
                r = func_002DCE50(p);
                if (arg2 & r) {
                    return p;
                }
                state = 0;
            }
        }
        cont = (s1 < (u32)p);
        p -= 1;
        if (!cont) {
            return NULL;
        }
    }
}
