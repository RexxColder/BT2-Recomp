#include "common.h"

s32 func_002DCE50(s32 arg0);

s32 func_002DCFE8(u32 arg0, s32 arg1, s32 arg2) {
    u32 p;
    u32 end;
    s32 state;
    s32 c;
    s32 r;

    p = arg0;
    end = arg0 + arg1;
    state = 0;
    for (;;) {
        if (!(p < end)) {
            return 0;
        }
        c = *(s8 *)p;
        p += 1;
        if (state == 0) {
            if (c == 0) {
                state = 1;
            }
        } else if (state == 1) {
            state = (c != 0) ? 0 : 2;
        } else if (state == 2) {
            if (c == 1) {
                state = 3;
            } else if (c != 0) {
                state = 0;
            }
        } else {
            r = func_002DCE50((s32)(p - 4));
            if (arg2 & r) {
                return (s32)(p - 4);
            }
            state = 0;
        }
    }
}
