#include "common.h"

u8 *func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5A18(u8 arg0);
s32 func_002D5B08(s32 arg0);

s32 func_002D55D0(s32 arg0, s32 arg1, s32 *arg2) {
    s32 s0 = arg1 & 0xFF;
    u8 *s1;

    *arg2 = 0;
    s1 = func_002D5210(arg0, s0);
    if (s1 != NULL) {
        if (func_002D5B08(s0) == 0xE0) {
            *arg2 = func_002D5A18(*(u8 *)(s1 + 0x1F));
            return 1;
        }
    }
    return 0;
}
