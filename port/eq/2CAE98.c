#include "common.h"

s32 func_002CB0A8(s32 arg0);

void func_002CAE98(s32 arg0, s32 *arg1, s32 *arg2) {
    u8 *t;
    u8 *inner;

    t = (u8 *)func_002CB0A8(arg0);
    if (t != NULL) {
        inner = *(u8 **)(t + 0x54);
        if (inner != NULL) {
            *arg2 = *(s32 *)(inner + 4);
            *arg1 = *(s32 *)(inner + 0);
            return;
        }
    }
    *arg1 = 0;
    *arg2 = 0;
}
