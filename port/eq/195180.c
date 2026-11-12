#include "common.h"

void func_00194948(s32 arg0);

s32 func_00195180(u8 *arg0) {
    u8 *p;
    u8 *q;
    s32 v;

    if (arg0 == 0) {
        return 0;
    }
    p = (u8 *)*(s32 *)(arg0 + 0x28);
    if (*(s32 *)p != (s32)0x00194948 /* PS2 class address (class 1: the table holds PS2 addresses) */) {
        return 0;
    }
    q = (u8 *)*(s32 *)(arg0 + 0x38);
    v = *(s32 *)(q + 0x60);
    if ((v & 1) == 0) {
        return 0;
    }
    *(s32 *)(q + 0x60) = v | 0x40;
    return 1;
}
