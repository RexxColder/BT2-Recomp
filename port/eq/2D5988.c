#include "common.h"

u8 *func_002D5210(u8 *arg0, s32 arg1);
u8 *func_002D5AC8(s32 arg0, s32 arg1);

u8 *func_002D5988(u8 *arg0, s32 arg1, s32 *arg2) {
    s32 s0;
    u8 *s1;
    u8 *v0;

    s0 = arg1 & 0xFF;
    *arg2 = -1;
    s1 = func_002D5210(arg0, s0);
    v0 = s1;
    if (s1 != NULL) {
        v0 = func_002D5AC8(s0, (s32)s1);
        if (v0 != NULL) {
            v0 = NULL;
            if (*(s32 *)(arg0 + 0xC) >= 0xD2) {
                v0 = (u8 *)1;
                *arg2 = s1[0x27];
            }
        }
    }
    return v0;
}
